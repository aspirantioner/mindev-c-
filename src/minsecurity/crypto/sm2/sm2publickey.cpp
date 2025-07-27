#include "mindev/include/minsecurity/crypto/sm2/sm2publickey.h"

namespace mindev::minsecurity::crypto::sm2 {

    std::vector<char> SM2PublicKey::Encrypt(const std::vector<char>& content){
        std::vector<char> res;
        if(content.size() == 0){
            return res;
        }
        static uint8_t pubkey[65]={0x4};
        gm_point_to_bytes(&publickey, pubkey+1);
        unsigned char c1[65] = {0};
        gm_sm2_crypt_init(&ctx,pubkey,65,1,c1);
        std::vector<char> c2(content.size());
        auto len = gm_sm2_crypt_update(&ctx,reinterpret_cast<const unsigned char*>(content.data()), content.size(),reinterpret_cast<unsigned char*>(c2.data()));
        unsigned char c3[32] = {0};
        len = gm_sm2_crypt_done(&ctx,reinterpret_cast<unsigned char*>(c2.data()+len), c3);
        // 构造完整密文：C1 || C2 || C3
        res.reserve(65 + c2.size() + 32);
        res.insert(res.end(), c1, c1 + 65);  // 添加 C1
        res.insert(res.end(), c2.begin(), c2.end());  // 添加 C2
        res.insert(res.end(), c3, c3 + 32);  // 添加 C3
        return res;
    }
    bool SM2PublicKey::Verify(const std::vector<char>& content,const std::vector<char>& digest){
        gm_bn_t dgst;
        gm_bn_from_bytes(dgst,reinterpret_cast<const uint8_t*>(digest.data()));
        return gm_do_verify(&publickey, dgst,reinterpret_cast<const unsigned char*>(content.data()));
    }

}