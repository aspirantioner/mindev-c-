#ifndef KEYCHAIN_H_
#define KEYCHAIN_H_

#include "mindev/include/minsecurity/crypto/sm2/sm2keypair.h"
#include "mindev/include/minsecurity/identity/db.h"
#include "mindev/include/minsecurity/identity/identity.h"
#include "mindev/include/minsecurity/identity/keyparam.h"
#include "mindev/include/packet/cpacket.h"
#include "mindev/include/packet/minpacket.h"
#include "mindev/include/security/safebag.h"
#include "selfencodingbase.h"
#include <cstdint>
#include <string>

namespace mindev::security {
class KeyChain {
public:
    bool Init(const std::string& passwd){
        if(!identity_db.Load(default_identity_dbpath,passwd)){
            return false;
        }
        auto ptr = identity_db.Find(default_identity_name);
        if(ptr==nullptr){
            auto sm2key_pair = minsecurity::crypto::sm2::SM2KeyPair::GenerateKeyPair();
            auto keyparam = mindev::minsecurity::identity::KeyParam((int)mindev::minsecurity::Common::PublicKeyAlgorithm::SM2,(int)mindev::minsecurity::Common::SignatureAlgorithm::SM3withSM2);
            minsecurity::identity::Identity new_identity = minsecurity::identity::Identity(default_identity_name,keyparam,sm2key_pair.GetSm2PrivateKey(),sm2key_pair.GetSm2PublicKey(),passwd,minsecurity::certificate::cert::Certificate(),false);
            if(passwd.size()!=0){
                new_identity.Lock(passwd,(int) mindev::minsecurity::Common::SymmetricAlgorithm::SM4ECB);
            }
            identity_db.Insert(new_identity.ToIdentityInfo());
            identity_db.Save();
            cur_identity = new_identity;
        }else{
            cur_identity = *ptr;
        }
        return true;
    }
    bool SetCurrentIdentity(minsecurity::identity::Identity& identity,const std::string& passwd){
        if(passwd.size() && identity.IsLocked()){
             if(!identity.UnLock(passwd,privateKeyEncryptionAlgorithm)){
                return false;
             }
        }
        cur_identity = identity;
        return true;
    }
    bool CheckIdentifyCanUseToSign(const mindev::minsecurity::identity::Identity& identity){
        return identity.HasPrivateKey() && !identity.IsLocked(); 
    }
    void Sign(mindev::packet::MINPacket& packet){
        CheckIdentifyCanUseToSign(cur_identity);
        auto rawdata = GetIdentifierAndReadOnlyValueFromPacket(packet);
        auto sign_res = cur_identity.Sign(rawdata);
        packet.signatureField.AddSignature(sign_res);
    }
    template<typename T>
    typename std::enable_if<std::is_same<T, mindev::packet::CPacket>::value || std::is_same<T, mindev::packet::Interest>::value ||std::is_same<T, mindev::packet::Data>::value,void>::type
    Sign(T& packet) {
        packet.FillDataToFields();
        Sign(packet.minPacket);
    }
    std::vector<uint8_t> SignBytes(const std::vector<uint8_t>& data){
        return this->cur_identity.Sign(data);
    }
    bool VerifyBytes(const std::vector<char>& data,const std::vector<char>& digest){
        return this->cur_identity.Verify(data,digest);
    }
    bool Verify(packet::MINPacket& minPacket){
        component::Signature signature = minPacket.signatureField.getSignature(0);
        std::string identityname = signature.GetSigInfo().getKeyLocator().GetIdentifier().ToUriTemp();
        auto identity = GetIdentityByName(identityname);
        if(!identity.has_value()){
            return false;
        }
        return identity.value().Verify(GetIdentifierAndReadOnlyValueFromPacket(minPacket),signature.GetSigValue().GetValue());
    }
    template<typename T>
    typename std::enable_if<std::is_same<T, mindev::packet::CPacket>::value || std::is_same<T, mindev::packet::Interest>::value ||std::is_same<T, mindev::packet::Data>::value,bool>::type
    Verify(T& packet) {
        packet.FillDataToFields();
        return Verify(packet.minPacket);
    }
    std::optional<minsecurity::identity::Identity> GetIdentityByName(const std::string& name){
        auto ptr = identity_db.Find(name);
        if(ptr==nullptr){
            return std::nullopt;
        }
        return minsecurity::identity::IdentityUtil::FromIdentityInfo(*ptr);
    }
    SafeBag ExportSafeBag(const minsecurity::identity::Identity& identity,const std::string& passwd){
        return SafeBag(identity.Dump(passwd));
    }
    void ImportSafeBag(const SafeBag& safebag,const std::string& passwd,bool force){
        if(safebag.GetValue().size()==0){
            return;
        }
        auto identity = minsecurity::identity::Identity::Load(safebag.GetValue(), passwd);
        if()
    }
    private:
        std::vector<char> GetIdentifierAndReadOnlyValueFromPacket(const mindev::packet::MINPacket& packet){
            std::vector<char> rawdata;
            std::vector<char> iblock_value;
            std::vector<char> rblock_value;
            //int total_length = 0;
        
            auto iblock = mindev::encoding::SelfEncodingBase().SelfWireEncode(packet.identifierField);
            if(iblock.has_value()){
                iblock_value = iblock.GetValue();
                //total_length += iblock_value.size();
            }
            
            auto rblock = mindev::encoding::SelfEncodingBase().SelfWireEncode(packet.readOnlyField);
            if(rblock.has_value()){
                rblock_value = rblock.GetValue();
                //total_length += rblock_value.size();
            }
            rawdata = iblock;
            rawdata.insert(rawdata.end(), rblock_value.begin(),rblock_value.end());
            return rawdata;
        }
        int privateKeyEncryptionAlgorithm = (int)minsecurity::Common::SymmetricAlgorithm::SM4ECB;
        inline static const std::string default_identity_name = "/localhost/operator";
        inline static const std::string default_identity_dbpath = "/usr/local/.mir/identity/";
        mindev::minsecurity::identity::IdentityDatabase identity_db;
        mindev::minsecurity::identity::Identity cur_identity;
};
}
#endif