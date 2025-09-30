#include "mindev/include/minsecurity/crypto/sm2/sm2privatekey.h"
#include "mindev/include/minsecurity/common.h"
#include "thirdparty/GmSSL/include/gmssl/error.h"
#include "thirdparty/GmSSL/include/gmssl/asn1.h"
#include <cstdint>

namespace mindev::minsecurity::crypto::sm2 {

    std::vector<char> SM2PrivateKey::Decrypt(const std::vector<char>& cipher,Common::Sm2CipherMode cipher_mode){
        std::vector<char> res;
        if(cipher.size()<=97 || cipher.size()-97 > SM2_MAX_PLAINTEXT_SIZE){
            return res;
        }
        res.resize(cipher.size()-97);
        size_t outlen = 0;
        SM2_CIPHERTEXT ciphertext;
        memcpy(ciphertext.point.x,cipher.data()+1,sizeof(ciphertext.point.x));
        memcpy(ciphertext.point.x,cipher.data()+1+sizeof(ciphertext.point.x),sizeof(ciphertext.point.y));
        if(cipher_mode == Common::Sm2CipherMode::C1C2C3){
            ciphertext.ciphertext_size = res.size();
            memcpy(ciphertext.ciphertext,cipher.data()+1+sizeof(ciphertext.point),ciphertext.ciphertext_size);
            memcpy(ciphertext.hash,cipher.data()+1+sizeof(ciphertext.point)+ciphertext.ciphertext_size,sizeof(ciphertext.hash));
        }else{
            ciphertext.ciphertext_size = res.size();
            memcpy(ciphertext.hash,cipher.data()+1+sizeof(ciphertext.point),sizeof(ciphertext.hash));
            memcpy(ciphertext.ciphertext,cipher.data()+1+sizeof(ciphertext.point)+sizeof(ciphertext.hash),ciphertext.ciphertext_size);
        }
        if(sm2_do_decrypt(this->sm2_key.get(),&ciphertext,reinterpret_cast<uint8_t*>(res.data()), &outlen)!=1 || outlen != res.size()){
            error_print();
            res.clear();
        }
        return res;
    }
    std::vector<char> SM2PrivateKey::Sign(const std::vector<char>& content){
        std::vector<char> res;
        if(content.size() == 0 ){
            return res;
        }
        SM2_SIGN_CTX sign_ctx;
        size_t siglen = 0;
        uint8_t sig[SM2_MAX_SIGNATURE_SIZE];
        if (sm2_sign_init(&sign_ctx, this->sm2_key.get(), SM2_DEFAULT_ID, SM2_DEFAULT_ID_LENGTH) != 1
            || sm2_sign_update(&sign_ctx,reinterpret_cast<const uint8_t*>(content.data()), content.size()) != 1
            || sm2_sign_finish(&sign_ctx, sig, &siglen) != 1) {
            error_print();
            res.clear();
            return res;
        }
        SM2_SIGNATURE sign;
        if (sm2_signature_from_der(&sign, reinterpret_cast<const uint8_t**>(&sig), &siglen) != 1
            || asn1_length_is_zero(siglen) != 1) {
            error_print();
            return res;
        }
        res.insert(res.end(),sign.r,sign.r+sizeof(sign.r));
        res.insert(res.end(),sign.s,sign.s+sizeof(sign.s));
        return res;
    }

}