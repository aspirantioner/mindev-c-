#ifndef SM2PRIVATEKEY_H_
#define SM2PRIVATEKEY_H_

#include "mindev/include/minsecurity/crypto/privatekeyinterface.h"
#include "thirdparty/GmSSL/include/gmssl/sm2_z256.h"
#include <cstdint>
#include "mindev/include/minsecurity/common.h"

namespace mindev::minsecurity::crypto::sm2 {
    class SM2PrivateKey:public mindev::minsecurity::crypto::PrivateKeyInterface{
public:
    SM2PrivateKey(){}

    SM2PrivateKey(std::shared_ptr<SM2_KEY> key){
         this->sm2_key = key;
    }
    void SetSm2key(std::shared_ptr<SM2_KEY> ptr){this->sm2_key = ptr;}
    std::vector<char> Decrypt(const std::vector<char>& cipher,Common::Sm2CipherMode cipher_mode = Common::Sm2CipherMode::C1C2C3);
    std::vector<char> Sign(const std::vector<char>& content);
    std::vector<char> GetBytes(){
        if(this->sm2_key.get()==nullptr){
            return std::vector<char>();
        }
        std::vector<char> res;
        res.reserve(32);
        for (int i = 3; i >= 0; --i) {            // 高位到低位
            for (int j = 7; j >= 0; --j) {        // 每个64位拆成字节，高字节在前
                res.push_back((this->sm2_key->private_key[i] >> (j * 8)) & 0xFF);
            }
        }
        return res;
    }
    bool SetBytes(std::vector<uint8_t>& key){
        if(key.size()!=32){
            return false;
        }
        sm2_z256_t r;
        sm2_z256_from_bytes(r, key.data());
        if(sm2_key_set_private_key(sm2_key.get(),r)!=1){
            return false;
        }
        return true;
    }
private:
    std::shared_ptr<SM2_KEY> sm2_key;
    };
}

#endif