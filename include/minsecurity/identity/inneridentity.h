#ifndef INNERIDENTITY_H_
#define INNERIDENTITY_H_

#include "mindev/include/minsecurity/certificate/cert/certificate.h"
#include "mindev/include/minsecurity/crypto/privatekeyinterface.h"
#include "mindev/include/minsecurity/identity/keyparam.h"
#include <string>

namespace mindev::minsecurity::identity {

class InnerIdentity{
public:
     InnerIdentity(const std::string& name,const mindev::minsecurity::identity::KeyParam& keyParam,
                    const std::vector<char>& prikey, const std::vector<char>& prikeyRawByte,
                    const std::vector<char>& pubkey,const std::string passwd,const mindev::minsecurity::certificate::cert::Certificate& cert,
                    bool isDefault) {
        Name = name;
        KeyParam = keyParam;
        Prikey = prikey;
        PrikeyRawByte = prikeyRawByte;
        Pubkey = pubkey;
        Passwd = passwd;
        Cert = cert;
    }
    
    
    InnerIdentity(){}
    
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
    std::vector<char> GetPriKey(){
        return Prikey;
    }
    void SetPrikey(const std::vector<char>& prikey){
        Prikey = prikey;
    }
    std::vector<char> GetPrikeyRawByte(){
        return PrikeyRawByte;
    }
    void SetPrikeyRawByte(const std::vector<char>& prikeyRawByte){
        PrikeyRawByte = prikeyRawByte;
    }
    std::vector<char> GetPubKey(){
        return Pubkey;
    }
    void SetPubkey(const std::vector<char>& pubkey){
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
    std::string ToString() {
        std::string res = "";
        return res+"InnerIdentity{" +
                "Name='" + Name + '\'' +
                ", KeyParam.PublicKeyAlgorithm=" + std::to_string(KeyParam.PublicKeyAlgorithm) +
                ", KeyParam.SignatureAlgorithm=" + std::to_string(KeyParam.SignatureAlgorithm) +
                ", Prikey=" + (Prikey.size() == 0 ? "null" : byteutils::VectorToHex(Prikey)) +
                ", Pubkey=" + (Pubkey.size() == 0 ? "null" : byteutils::VectorToHex(Pubkey)) +
                ", Passwd='" + Passwd + '\'' +
                ", Cert='" + Cert.ToString() + '\'' +
                ", PrikeyRawByte='" + byteutils::VectorToHex(PrikeyRawByte) + '\''+
                '}';
    }
private:
    std::string Name;
    mindev::minsecurity::identity::KeyParam KeyParam;
    std::vector<char> Prikey;
    std::vector<char> PrikeyRawByte;
    std::vector<char> Pubkey;
    std::string Passwd;
    mindev::minsecurity::certificate::cert::Certificate Cert;
};

}
#endif