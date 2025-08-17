#include "mindev/include/minsecurity/crypto/sm2/sm2publickey.h"
#include "mindev/include/minsecurity/common.h"
#include "thirdparty/GmSSL/include/gmssl/error.h"
#include <cstddef>
#include <cstdint>

namespace mindev::minsecurity::crypto::sm2 {

    std::vector<char> SM2PublicKey::Encrypt(const std::vector<char>& content,Common::Sm2CipherMode cipher_mode = Common::Sm2CipherMode::C1C2C3){
        std::vector<char> res;
        static const char sm2_prefix =  0x04;
        if(content.size() == 0 || SM2_MAX_PLAINTEXT_SIZE < content.size()){
            return res;
        }
        SM2_CIPHERTEXT ciphertext;
        if(sm2_do_encrypt(this->sm2_key.get(),reinterpret_cast<const uint8_t*>(content.data()),content.size(), ciphertext)!=1){
            error_print();
            return res;
        }
        res.emplace_back(sm2_prefix);
        res.insert(res.end(),ciphertext.point.x,sizeof(ciphertext.point.x));
        res.insert(res.end(),ciphertext.point.y,sizeof(ciphertext.point.y));
        if(cipher_mode == Common::Sm2CipherMode::C1C2C3){
            res.insert(res.end(),ciphertext.ciphertext,ciphertext.ciphertext+ciphertext.ciphertext_size);
            res.insert(res.end(),ciphertext.hash,ciphertext.hash+sizeof(ciphertext.hash));
        }else{
            res.insert(res.end(),ciphertext.hash,ciphertext.hash+sizeof(ciphertext.hash));
            res.insert(res.end(),ciphertext.ciphertext,ciphertext.ciphertext+ciphertext.ciphertext_size);
        }
        return res;
    }
    bool SM2PublicKey::Verify(const std::vector<char>& content){
        SM2_VERIFY_CTX verify_ctx;
        SM2_SIGNATURE sign;
        memcpy(sign.r, content.data(), sizeof(sign.r));
        memcpy(sign.s, content.data()+sizeof(sign.r), sizeof(sign.s));
        uint8_t sig[SM2_MAX_SIGNATURE_SIZE];
        size_t siglen;
        if(sm2_signature_to_der(&sign,reinterpret_cast<uint8_t**>(&sig),&siglen)!=1){
            return false;
        }
        if (sm2_verify_init(&verify_ctx, this->sm2_key.get(), SM2_DEFAULT_ID, SM2_DEFAULT_ID_LENGTH) != 1
            || sm2_verify_update(&verify_ctx,reinterpret_cast<const uint8_t*>(content.data()), content.size()) != 1
            || sm2_verify_finish(&verify_ctx, sig, siglen) != 1) {
            error_print();
            return false;
        }
        return true;
    }

}