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
                    const mindev::minsecurity::crypto::PublicKeyInterface& pubkey,const std::string passwd,const mindev::minsecurity::cert::Certificate& cert,
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
                    const std::string& passwd,const mindev::minsecurity::cert::Certificate& cert,
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
private:
    std::string Name;
    mindev::minsecurity::identity::KeyParam KeyParam;
    mindev::minsecurity::crypto::PrivateKeyInterface Prikey;
    std::vector<char> PrikeyRawByte;
    mindev::minsecurity::crypto::PublicKeyInterface Pubkey;
    std::string Passwd;
    mindev::minsecurity::cert::Certificate Cert;
    bool IsDefault;
};

}
#endif