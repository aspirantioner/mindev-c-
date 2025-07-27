#ifndef SM2PRIVATEKEY_H_
#define SM2PRIVATEKEY_H_

#include "mindev/include/gm/gm.h"
#include "mindev/include/gm/sm2.h"
#include "mindev/include/minsecurity/crypto/privatekeyinterface.h"
#include <cstdint>
namespace mindev::minsecurity::crypto::sm2 {
    class SM2PrivateKey:public mindev::minsecurity::crypto::PrivateKeyInterface{
public:
    SM2PrivateKey(){}

    SM2PrivateKey(const gm_bn_t key){
        memcpy(privatekey,key ,sizeof(key));
    }
    std::vector<char> Decrypt(const std::vector<char>& cipher);
    std::vector<char> Sign(const std::vector<char>& content);
private:
    gm_bn_t privatekey;
    gm_sm2_context ctx;
    
    };
}

#endif