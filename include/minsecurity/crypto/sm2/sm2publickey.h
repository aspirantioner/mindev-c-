#ifndef SM2PUBLICKEY_H_
#define SM2PUBLICKEY_H_

#include "thirdparty/GmSSL/include/gmssl/sm2.h"
#include "mindev/include/minsecurity/crypto/publickeyinterface.h"
#include "thirdparty/GmSSL/include/gmssl/sm2_z256.h"
#include <cstdint>
#include "mindev/include/minsecurity/common.h"

namespace mindev::minsecurity::crypto::sm2 {
    class SM2PublicKey:public mindev::minsecurity::crypto::PublicKeyInterface{
public:
    SM2PublicKey(){}

    SM2PublicKey(std::shared_ptr<SM2_KEY> key){
        this->sm2_key = key;
    }
    void SetSm2key(std::shared_ptr<SM2_KEY> ptr){this->sm2_key = ptr;}
    std::vector<char> Encrypt(const std::vector<char>& content,mindev::minsecurity::Common::Sm2CipherMode cipher_mode = mindev::minsecurity::Common::Sm2CipherMode::C1C2C3);
    bool Verify(const std::vector<char>& content,const std::vector<char>& digest);
    std::vector<char> GetBytes()const{
        std::vector<char> res;
        if(this->sm2_key.get()==nullptr){
            return res;
        }
        if (sm2_z256_point_is_at_infinity(&this->sm2_key->public_key) == 1) {
		    return res;
        } else {
            uint8_t bytes[64];
            sm2_z256_point_to_bytes(&this->sm2_key->public_key, bytes);
            res.insert(res.end(), bytes,bytes+64);
        }
        return res;
    }
    bool SetBytes(const std::vector<uint8_t>& key){
        if(key.size()!=64){
            return false;
        }
        SM2_Z256_POINT P;
        if(sm2_z256_point_from_bytes(&P, key.data())!=1){
            return false;
        }
        if(sm2_key_set_public_key(sm2_key.get(),&P)!=1){
            return false;
        }
        return true;
    }
private:
    std::shared_ptr<SM2_KEY> sm2_key;
    
    };
}

#endif