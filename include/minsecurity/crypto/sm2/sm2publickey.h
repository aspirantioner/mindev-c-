#ifndef SM2PUBLICKEY_H_
#define SM2PUBLICKEY_H_

#include "mindev/include/gm/gm.h"
#include "mindev/include/gm/sm2.h"
#include "mindev/include/minsecurity/crypto/publickeyinterface.h"
#include <cstdint>
namespace mindev::minsecurity::crypto::sm2 {
    class SM2PublicKey:public mindev::minsecurity::crypto::PublicKeyInterface{
public:
    SM2PublicKey(){}

    SM2PublicKey(const gm_point_t key){
        memcpy(publickey.X,key.X ,sizeof(key.X));
        memcpy(publickey.Y,key.Y ,sizeof(key.Y));
        memcpy(publickey.Z,key.Z ,sizeof(key.Z));
    }
    std::vector<char> Encrypt(const std::vector<char>& content);
    bool Verify(const std::vector<char>& content,const std::vector<char>& digest);
private:
    gm_point_t publickey;
    gm_sm2_context ctx;
    
    };
}

#endif