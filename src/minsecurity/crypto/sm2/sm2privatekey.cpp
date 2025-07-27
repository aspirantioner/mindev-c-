#include "mindev/include/minsecurity/crypto/sm2/sm2privatekey.h"

namespace mindev::minsecurity::crypto::sm2 {

    std::vector<char> SM2PrivateKey::Decrypt(const std::vector<char>& cipher){
        std::vector<char> res;
        if(cipher.size() <= 65+32){
            return res;
        }
        static uint8_t prikey[32]={0x0};
        gm_bn_to_bytes(privatekey,prikey);
        unsigned char c1[65] = {0};
        memcpy(c1, cipher.data(), sizeof(c1));
        gm_sm2_crypt_init(&ctx,prikey,32,0,c1);
        std::vector<char> c2(cipher.size()-97);
        auto len = gm_sm2_crypt_update(&ctx,reinterpret_cast<const unsigned char*>(cipher.data()+65), c2.size(),reinterpret_cast<unsigned char*>(c2.data()));
        unsigned char c3[32] = {0};
        len = gm_sm2_crypt_done(&ctx,reinterpret_cast<unsigned char*>(c2.data()+len), c3);
        return c2;
    }
    std::vector<char> SM2PrivateKey::Sign(const std::vector<char>& content){
        if(content.size() == 0 || content.size()!=32){
            return std::vector<char>();
        }
        gm_bn_t dgst;
        gm_bn_from_bytes(dgst, reinterpret_cast<const uint8_t*> (content.data()));      
        std::vector<char> res(64);
        if(gm_do_sign(privatekey, dgst,reinterpret_cast<unsigned char*>(res.data()))==1){
            return res;
        }else{
            return std::vector<char>();
        }
    }

}