#ifndef IDENTITY_H_
#define IDENTITY_H_

#include "mindev/include/minsecurity/certificate/cert/certificate.h"
#include "mindev/include/minsecurity/crypto/privatekeyinterface.h"
#include "mindev/include/minsecurity/identity/keyparam.h"
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
    
    inline bool IsLocked(){
        return PrikeyRawByte.size()!=0 ;
    }
    inline bool HasPrivateKey(){
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