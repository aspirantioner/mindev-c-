#ifndef SM2PRIVATEKEY_H_
#define SM2PRIVATEKEY_H_

#include "mindev/include/minsecurity/crypto/privatekeyinterface.h"

namespace mindev::minsecurity::crypto::sm2 {
    class SM2PrivateKey:public mindev::minsecurity::crypto::PrivateKeyInterface{
public:
    SM2PrivateKey(){}

    SM2PrivateKey(std::shared_ptr<SM2_KEY> key){
         this->sm2_key = key;
    }
    void SetSm2key(std::shared_ptr<SM2_KEY> ptr){this->sm2_key = ptr;}
    std::vector<char> Decrypt(const std::vector<char>& cipher);
    std::vector<char> Sign(const std::vector<char>& content);
    std::vector<char> GetBytes(){
        if(this->sm2_key.get()==nullptr){
            return std::vector<char>();
        }
        std::vector<char> res;
        res.reserve(32);
        for (int i = 3; i >= 0; --i) {            // 高位到低位
            for (int j = 7; j >= 0; --j) {        // 每个64位拆成字节，高字节在前
                res.push_back((this->sm2_key->privatekey[i] >> (j * 8)) & 0xFF);
            }
        }
        return res;
    }
private:
    std::shared_ptr<SM2_KEY> sm2_key;
    };
}

#endif