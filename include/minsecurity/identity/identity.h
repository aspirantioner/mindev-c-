#ifndef IDENTITY_H_
#define IDENTITY_H_

#include "mindev/include/minsecurity/certificate/cert/certificate.h"
#include "mindev/include/minsecurity/certificate/cert/certutils.h"
#include "mindev/include/minsecurity/common.h"
#include "mindev/include/minsecurity/crypto/keyutils.h"
#include "mindev/include/minsecurity/crypto/privatekeyinterface.h"
#include "mindev/include/minsecurity/crypto/sm4.h"
#include "mindev/include/minsecurity/identity/db.h"
#include "mindev/include/minsecurity/identity/identityutil.h"
#include "mindev/include/minsecurity/identity/inneridentity.h"
#include "mindev/include/minsecurity/identity/keyparam.h"
#include <cstdint>
#include <string>

namespace mindev::minsecurity::identity {

class Identity{
public:
     Identity(const std::string& name,const mindev::minsecurity::identity::KeyParam& keyParam,
                    const mindev::minsecurity::crypto::PrivateKeyInterface& prikey, const std::vector<char>& prikeyRawByte,
                    const mindev::minsecurity::crypto::PublicKeyInterface& pubkey,const std::string passwd,const mindev::minsecurity::certificate::cert::Certificate& cert,
                    bool isDefault) {
        Name = name;
        KeyParam = keyParam;
        Prikey = prikey;
        PrikeyRawByte = prikeyRawByte;
        Pubkey = pubkey;
        Passwd = passwd;
        Cert = cert;
        IsDefault = isDefault;
    }

    /**
     * 参数中不包含PrikeyRawByte
     * @author hongyu guo
     * @date 2021/3/12
    **/
    Identity(const std::string& name, const mindev::minsecurity::identity::KeyParam& keyParam,
                    const mindev::minsecurity::crypto::PrivateKeyInterface& prikey,mindev::minsecurity::crypto::PublicKeyInterface& pubkey,
                    const std::string& passwd,const mindev::minsecurity::certificate::cert::Certificate& cert,
                    bool isDefault) {
        Name = name;
        KeyParam = keyParam;
        Prikey = prikey;
        Pubkey = pubkey;
        Passwd = passwd;
        Cert = cert;
        IsDefault = isDefault;
    }
    
    Identity(){}
    
    inline bool IsLocked()const{
        return PrikeyRawByte.size()!=0 ;
    }
    inline bool HasPrivateKey()const{
        return Prikey.GetBytes().size()!=0 || PrikeyRawByte.size()!=0;
    }
    std::string GetName() const{
        return Name;
    }
    void SetName(const std::string& name) {
        this->Name = name;
    }
    mindev::minsecurity::identity::KeyParam GetKeyParam(){
        return KeyParam;
    }
    void SetKeyParam(const mindev::minsecurity::identity::KeyParam& keyParam){
        KeyParam = keyParam;
    }
    mindev::minsecurity::crypto::PrivateKeyInterface GetPriKey(){
        return Prikey;
    }
    void SetPrikey(const mindev::minsecurity::crypto::PrivateKeyInterface& prikey){
        Prikey = prikey;
    }
    std::vector<char> GetPrikeyRawByte(){
        return PrikeyRawByte;
    }
    void SetPrikeyRawByte(const std::vector<char>& prikeyRawByte){
        PrikeyRawByte = prikeyRawByte;
    }
    mindev::minsecurity::crypto::PublicKeyInterface GetPubKey(){
        return Pubkey;
    }
    void SetPubkey(const mindev::minsecurity::crypto::PublicKeyInterface& pubkey){
        Pubkey = pubkey;
    }
    std::string GetPasswd(){
        return Passwd;
    }
    void SetPasswd(const std::string& passwd){
        Passwd = passwd;
    }
    mindev::minsecurity::certificate::cert::Certificate GetCert(){
        return Cert;
    }
    void SetCert(const mindev::minsecurity::certificate::cert::Certificate& cert){
        Cert = cert;
    }
    bool Isdefault(){
        return IsDefault;
    }
    void SetDefault(bool Default){
        IsDefault = Default;
    }
    std::string ToString() {
        std::string res = "";
        return res + "Identity{" +
                "Name='" + Name + '\'' +
                ", KeyParam.signAlgo=" + std::to_string(KeyParam.SignatureAlgorithm) +
                ", KeyParam.pubAlgo=" + std::to_string(KeyParam.PublicKeyAlgorithm) +
                ", Prikey=" + (Prikey.GetBytes().size() != 0 ? byteutils::VectorToHex(Prikey.GetBytes()) : "null") +
                ", pubKey=" + (Pubkey.GetBytes().size() != 0 ? byteutils::VectorToHex(Pubkey.GetBytes()) : "null") +
                ", PrikeyRawByte=" + (PrikeyRawByte.size() == 0 ? "null":byteutils::VectorToHex(PrikeyRawByte)) +
                ", Passwd='" + Passwd + '\'' +
                ", Cert=" + Cert.ToString() +
                ", isDefault=" + std::to_string(IsDefault) +
                '}';
    }
    IdentityInfo ToIdentityInfo(){
        IdentityInfo res;
        res.name = Name;
        res.pubkey = byteutils::VectorToString(Pubkey.GetBytes());
        res.prikey = byteutils::VectorToString(Prikey.GetBytes());
        res.pubkey_algo = KeyParam.PublicKeyAlgorithm;
        res.signature_algo = KeyParam.SignatureAlgorithm;
        res.cert = certificate::cert::CertUtils::ToPem(Cert,"",mindev::minsecurity::Common::SymmetricAlgorithm::SM4ECB);
        res.prikey_raw_byte = byteutils::VectorToString(PrikeyRawByte);
        return res;
    }
    bool Lock(const std::string& passwd,int algo){
        switch(algo){
            case mindev::minsecurity::Common::SymmetricAlgorithm::SM4ECB:
                auto passhash = crypto::KeyUtils::Get16BytePasswd(byteutils::StringToVector<uint8_t>(passwd));
                auto prikey = Prikey.GetBytes();
                auto enckey = mindev::minsecurity::crypto::SM4::EncryptECBPadding(passhash,prikey);
                PrikeyRawByte = enckey;
                return true;
            default:
                return false;
        }
        return false;
    }
    std::vector<uint8_t> Sign(const std::vector<uint8_t>& content){
        if(KeyParam.PublicKeyAlgorithm == Common::PublicKeyAlgorithm::SM2 && KeyParam.SignatureAlgorithm == Common::SignatureAlgorithm::SM3withSM2){
            return (crypto::sm2::SM2PrivateKey*)(&Prikey)->Sign(content);
        }
        return std::vector<uint8_t>();
    }
    bool UnLock(const std::string& passwd,int algo){
        switch (algo) { 
            case (int)minsecurity::Common::SymmetricAlgorithm::SM4ECB:
                if(passwd.size()==0){
                    return false;
                }
                auto sm4key = minsecurity::crypto::KeyUtils::Get16BytePasswd(passwd);
                auto dec = minsecurity::crypto::SM4::DecryptECBPadding(sm4key,PrikeyRawByte);
                
        }
    }
    bool Verify(std::vector<char>& msg,std::vector<char>& digest){
        if(msg.size() == 0 || digest.size() == 0){
            return false;
        }
        if(KeyParam.PublicKeyAlgorithm == Common::PublicKeyAlgorithm::SM2 && KeyParam.SignatureAlgorithm == Common::SignatureAlgorithm::SM3withSM2){
            return (crypto::sm2::SM2PublicKey*)(&Pubkey)->Verify(msg,digest);
        }
        return false;
    }
    std::vector<uint8_t> Decrypt(std::vector<uint8_t>& cipher){
        return (crypto::sm2::SM2PrivateKey*)(&Prikey)->Decrypt(cipher);
    }
    std::vector<uint8_t> Encrypt(std::vector<uint8_t>& content){
        return (crypto::sm2::SM2PublicKey*)(&Pubkey)->Encrypt(content);
    }
    std::vector<uint8_t> Dump(const std::string& passwd){
        InnerIdentity inneridentity = IdentityUtil::ParseIdentityToInner(this);
        json j = inneridentity;
        if(passwd.size()>0){
            auto sm4key = crypto::KeyUtils::Get16BytePasswd(passwd);
            auto cipher = minsecurity::crypto::SM4::EncryptCBCPadding(sm4key, byteutils::GenerateRandomVector<uint8_t>(16),byteutils::StringToVector<uint8_t>(j.dump()));
            return Base64::Encode(byteutils::VectorToString(cipher));
        }
        return Base64::Encode(j.dump());
    }
    static Identity Load(const std::vector<uint8_t>& serialbyte,const std::string& passwd){
        auto json_str = Base64::Decode(byteutils::VectorToString(serialbyte));
        if(passwd.size()>0){
            auto sm4key = crypto::KeyUtils::Get16BytePasswd(passwd);
            json_str = minsecurity::crypto::SM4::DecryptCBCPadding(sm4key, byteutils::GenerateRandomVector<uint8_t>(16), byteutils::StringToVector<uint8_t>(json_str));
        }
        auto j = json::parse(json_str.data());
        auto inneridentity = json::get<InnerIdentity>(j);
        return IdentityUtil::ParseIdentityToInner(inneridentity);
    } 
private:
    std::string Name;
    mindev::minsecurity::identity::KeyParam KeyParam;
    mindev::minsecurity::crypto::PrivateKeyInterface Prikey;
    std::vector<char> PrikeyRawByte;
    mindev::minsecurity::crypto::PublicKeyInterface Pubkey;
    std::string Passwd;
    mindev::minsecurity::certificate::cert::Certificate Cert;
    bool IsDefault;
};

}
#endif