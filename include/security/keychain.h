#ifndef KEYCHAIN_H_
#define KEYCHAIN_H_

#include "mindev/include/minsecurity/identity/identityutil.h"
#include "mindev/include/minsecurity/crypto/sm2/sm2keypair.hpp"
#include "mindev/include/minsecurity/identity/db.h"
#include "mindev/include/minsecurity/identity/identity.h"
#include "mindev/include/minsecurity/identity/identityutil.h"
#include "mindev/include/minsecurity/identity/keyparam.h"
#include "mindev/include/packet/cpacket.h"
#include "mindev/include/packet/interest.h"
#include "mindev/include/packet/minpacket.h"
#include "mindev/include/security/safebag.h"
#include "mindev/include/encoding/selfencodingbase.h"
#include <cstdint>
#include <string>

namespace mindev::security {
class KeyChain {
public:
    inline int GetInitState()const{
        return init_state;
    }
    inline bool IsInKeyChain(const std::string& username){
        return identity_db.Find(username);
    }
    bool CreateIdentity(const std::string& username,const std::string& user_passwd=""){
        if(GetInitState()!=0){
            return false;
        }
        auto ptr = identity_db.Find(username);
        if(ptr==nullptr){
            auto sm2key_pair = minsecurity::crypto::sm2::SM2KeyPair::GenerateKeyPair();
            auto pubkey = sm2key_pair.GetSm2PublicKey().GetBytes();
            auto keyparam = mindev::minsecurity::identity::KeyParam((int)mindev::minsecurity::Common::PublicKeyAlgorithm::SM2,(int)mindev::minsecurity::Common::SignatureAlgorithm::SM3withSM2);
            minsecurity::identity::Identity new_identity = minsecurity::identity::Identity(username,keyparam,sm2key_pair.GetSm2PrivateKey(),sm2key_pair.GetSm2PublicKey(),user_passwd,minsecurity::certificate::cert::Certificate(),false);
            if(new_identity.GetPasswd().size()!=0){
                OH_LOG_INFO(LOG_APP,"new user has passwd .");
                if(!new_identity.Lock(new_identity.GetPasswd(),(int) mindev::minsecurity::Common::SymmetricAlgorithm::SM4ECB)){
                    OH_LOG_ERROR(LOG_APP,"new user lock failed!");
                    return false;
                };
            }
            identity_db.Insert(new_identity.ToIdentityInfo());
           
            if( identity_db.Save()!=0){
                OH_LOG_ERROR(LOG_APP,"keychain new identity save error!");
                return false;
            }
            cur_identity = new_identity;
        }else{
            auto identity = mindev::minsecurity::identity::IdentityUtil::FromIdentityInfo(*ptr);
            if(!identity.has_value()){
                init_state = -1;
            }
            cur_identity = std::move(identity.value());    
        }
        return true;
    }
    void Init(const std::string& passwd,const std::string& passwd_digest_filename,const std::string& user_identity_filename,const std::string& default_identity_name,const std::string& user_passwd=""){
        init_state = identity_db.Load(passwd,passwd_digest_filename,user_identity_filename);
        if(init_state!=0){
            OH_LOG_ERROR(LOG_APP,"keychain init error!");
            return;
        }
        auto ptr = identity_db.Find(default_identity_name);
        if(ptr==nullptr){
            auto sm2key_pair = minsecurity::crypto::sm2::SM2KeyPair::GenerateKeyPair();
            auto pubkey = sm2key_pair.GetSm2PublicKey().GetBytes();
            auto keyparam = mindev::minsecurity::identity::KeyParam((int)mindev::minsecurity::Common::PublicKeyAlgorithm::SM2,(int)mindev::minsecurity::Common::SignatureAlgorithm::SM3withSM2);
            minsecurity::identity::Identity new_identity = minsecurity::identity::Identity(default_identity_name,keyparam,sm2key_pair.GetSm2PrivateKey(),sm2key_pair.GetSm2PublicKey(),user_passwd,minsecurity::certificate::cert::Certificate(),false);
            if(new_identity.GetPasswd().size()!=0){
                OH_LOG_INFO(LOG_APP,"new user has passwd .");
                if(!new_identity.Lock(new_identity.GetPasswd(),(int) mindev::minsecurity::Common::SymmetricAlgorithm::SM4ECB)){
                    init_state = -1;
                    OH_LOG_ERROR(LOG_APP,"new user lock failed!");
                    return;
                };
            }
            identity_db.Insert(new_identity.ToIdentityInfo());
            init_state = identity_db.Save(user_identity_filename);
            if(init_state != 0){
                OH_LOG_ERROR(LOG_APP,"keychain new identity save error!");
                return;
            }
            cur_identity = new_identity;
        }else{
            auto identity = mindev::minsecurity::identity::IdentityUtil::FromIdentityInfo(*ptr);
            if(!identity.has_value()){
                init_state = -1;
            }
            cur_identity = std::move(identity.value());    
        }
        init_state = 0;
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
    inline mindev::minsecurity::identity::Identity GetCurrentIdentity()const{
        return this->cur_identity;
    }
    bool CheckIdentifyCanUseToSign(const mindev::minsecurity::identity::Identity& identity){
        return identity.HasPrivateKey() && !identity.IsLocked(); 
    }
    void Sign(mindev::packet::MINPacket& packet){
        CheckIdentifyCanUseToSign(cur_identity);
        auto rawdata = GetIdentifierAndReadOnlyValueFromPacket(packet);
        auto sign_res = cur_identity.Sign(rawdata);
        packet.signatureField.AddSignature(mindev::component::Signature(cur_identity,sign_res));
    }
    template<typename T>
    typename std::enable_if<std::is_same<T, mindev::packet::CPacket>::value || std::is_same<T, mindev::packet::Interest>::value ||std::is_same<T, mindev::packet::Data>::value,void>::type
    Sign(T& packet) {
        packet.FillDataToFields();
        Sign(packet.minPacket);
    }
    std::vector<uint8_t> SignBytes(const std::vector<uint8_t>& data){
        return this->cur_identity.Sign(byteutils::Uint8ToChar(data));
    }
    bool VerifyBytes(const std::vector<char>& data,const std::vector<char>& digest){
        return this->cur_identity.Verify(data,digest);
    }
    bool Verify(packet::MINPacket& minPacket){
        component::Signature signature = minPacket.signatureField.GetSignature(0);
        std::string identityname = signature.GetSigInfo().GetKeyLactor().GetIdentifier().ToUriTemp();
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
    }
    bool ImportVmsCert(const std::string& identity_name,const std::string& passwd){
        auto cert=minsecurity::certificate::cert::CertUtils::FromPem(identity_name, byteutils::StringToVector<uint8_t>(passwd), int(minsecurity::Common::SymmetricAlgorithm::SM4ECB));
        if(cert.IsValid()){
            return false;
        }  
        auto ptr = identity_db.Find(identity_name);
        if(ptr!=nullptr){
            ptr->cert = minsecurity::certificate::cert::CertUtils::ToPem(cert,std::vector<uint8_t>(),(int)mindev::minsecurity::Common::SymmetricAlgorithm::SM4ECB);
            identity_db.Update(*ptr);
            identity_db.Save();
        }else{
            minsecurity::identity::Identity new_identity;
            new_identity.SetName(cert.getIssueTo());
            new_identity.SetCert(cert);
            new_identity.SetKeyParam(minsecurity::identity::KeyParam(cert.GetPublicKeyAlgorithm(), cert.GetSignatureAlgorithm()));
            new_identity.SetPubkey(cert.GetPublicKey());
            identity_db.Update(new_identity.ToIdentityInfo());
            identity_db.Save();
        }
        return true;
    }
    private:
        std::vector<char> GetIdentifierAndReadOnlyValueFromPacket(mindev::packet::MINPacket& packet){
            std::vector<char> rawdata;
            std::vector<char> iblock_value;
            std::vector<char> rblock_value;
            //int total_length = 0;
        
            auto iblock = mindev::encoding::SelfEncodingBase().SelfWireEncode(packet.identifierField);
            if(iblock.has_value()){
                iblock_value = iblock.value().GetValue();
                //total_length += iblock_value.size();
            }
            
            auto rblock = mindev::encoding::SelfEncodingBase().SelfWireEncode(packet.readOnlyField);
            if(rblock.has_value()){
                rblock_value = rblock.value().GetValue();
                //total_length += rblock_value.size();
            }
            rawdata = iblock_value;
            rawdata.insert(rawdata.end(), rblock_value.begin(),rblock_value.end());
            return rawdata;
        }
        int privateKeyEncryptionAlgorithm = (int)minsecurity::Common::SymmetricAlgorithm::SM4ECB;
        mindev::minsecurity::identity::IdentityDatabase identity_db;
        mindev::minsecurity::identity::Identity cur_identity;
        int init_state; 
};
}
#endif