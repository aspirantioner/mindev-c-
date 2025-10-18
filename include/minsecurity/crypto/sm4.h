#ifndef SM4_H_
#define SM4_H_

#define ENABLE_SM4_ECB 1

#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "thirdparty/GmSSL/include/gmssl/error.h"
#include "thirdparty/GmSSL/include/gmssl/sm4.h"
#ifdef __cplusplus
}
#endif

#include <cstdint>
#include <optional>
#include <vector>

namespace mindev::minsecurity::crypto {
    class SM4 {
public:
    inline static const std::string ALGORITHM_NAME = "SM4";
    inline static const std::string ALGORITHM_NAME_ECB_PADDING = "SM4/ECB/PKCS5Padding";
    inline static const std::string ALGORITHM_NAME_ECB_NOPADDING = "SM4/ECB/NoPadding";
    inline static const std::string ALGORITHM_NAME_CBC_PADDING = "SM4/CBC/PKCS5Padding";
    inline static const std::string ALGORITHM_NAME_CBC_NOPADDING = "SM4/CBC/NoPadding";
    
    static std::vector<uint8_t> EncryptCBCPadding(const std::vector<uint8_t>&  key,const std::vector<uint8_t>& iv,const std::vector<uint8_t>& data){
        static  SM4_KEY enc_key;
        std::vector<uint8_t> res;
        if(key.size() != SM4_BLOCK_SIZE || iv.size() != SM4_BLOCK_SIZE){
            return res;
        }
        sm4_set_encrypt_key(&enc_key,key.data());
        res.resize((data.size()/SM4_BLOCK_SIZE+1)*SM4_BLOCK_SIZE);
        size_t outlen = 0;
        sm4_cbc_padding_encrypt(&enc_key,iv.data(), data.data(), data.size(),res.data(), &outlen);
        return std::vector<uint8_t>(res.begin(),res.begin()+outlen);
    }
    static std::vector<uint8_t> DecryptCBCPadding(const std::vector<uint8_t>&  key,const std::vector<uint8_t>& iv,const std::vector<uint8_t>& data){
        static  SM4_KEY dec_key;
        std::vector<uint8_t> res;
        if(key.size() != SM4_BLOCK_SIZE || iv.size() != SM4_BLOCK_SIZE){
            return res;
        }
        sm4_set_decrypt_key(&dec_key,key.data());
        res.resize((data.size()/SM4_BLOCK_SIZE+1)*SM4_BLOCK_SIZE);
        size_t outlen = 0;
        sm4_cbc_padding_decrypt(&dec_key,iv.data(), data.data(), data.size(),res.data(), &outlen);
//         if(res.size() != outlen){
//             res.clear();
//         }
        return std::vector<uint8_t>(res.begin(),res.begin()+outlen);
    }
    static std::vector<uint8_t> EncryptCBCNoPadding(const std::vector<uint8_t>&  key,std::vector<uint8_t>& iv,const std::vector<uint8_t>& data){
        static  SM4_KEY enc_key;
        std::vector<uint8_t> res;
        if(key.size() != SM4_BLOCK_SIZE || iv.size() != SM4_BLOCK_SIZE || data.size() % SM4_BLOCK_SIZE != 0 ){
            return res;
        }
        sm4_set_encrypt_key(&enc_key, key.data());
        res.resize(data.size());
        sm4_cbc_encrypt_blocks(&enc_key, iv.data(), data.data(), data.size() / SM4_BLOCK_SIZE, res.data());
        return res;
    }
    static std::vector<uint8_t> DecryptCBCNoPadding(const std::vector<uint8_t>&  key,std::vector<uint8_t>& iv,const std::vector<uint8_t>& data){
        static  SM4_KEY dec_key;
        std::vector<uint8_t> res;
        if(key.size() != SM4_BLOCK_SIZE || iv.size() != SM4_BLOCK_SIZE || data.size() % SM4_BLOCK_SIZE != 0 ){
            return res;
        }
        sm4_set_decrypt_key(&dec_key, key.data());
        res.resize(data.size());
        sm4_cbc_decrypt_blocks(&dec_key, iv.data(), data.data(), data.size() / SM4_BLOCK_SIZE, res.data());
        return res;
    }
    static std::vector<uint8_t> EncryptECBNoPadding(const std::vector<uint8_t>&  key,const std::vector<uint8_t>& data){
        static  SM4_KEY enc_key;
        std::vector<uint8_t> res;
        if(key.size() != SM4_BLOCK_SIZE || data.size() % SM4_BLOCK_SIZE != 0 ){
            return res;
        }
        sm4_set_encrypt_key(&enc_key, key.data());
        res.resize(data.size());
        sm4_encrypt_blocks(&enc_key, data.data(), data.size() / SM4_BLOCK_SIZE, res.data());
        return res;
    }
    static std::vector<uint8_t> DecryptECBNoPadding(const std::vector<uint8_t>&  key,const std::vector<uint8_t>& data){
        static  SM4_KEY dec_key;
        std::vector<uint8_t> res;
        if(key.size() != SM4_BLOCK_SIZE || data.size() % SM4_BLOCK_SIZE != 0 ){
            return res;
        }
        sm4_set_decrypt_key(&dec_key, key.data());
        res.resize(data.size());
        sm4_encrypt_blocks(&dec_key, data.data(), data.size() / SM4_BLOCK_SIZE, res.data());
        return res;
    }
    static std::vector<uint8_t> EncryptECBPadding(const std::vector<uint8_t>&  key,std::vector<uint8_t>& data){
        static SM4_ECB_CTX ctx;
        std::vector<uint8_t> res;
        if(key.size() != SM4_BLOCK_SIZE){
            return res;
        }
        sm4_ecb_encrypt_init(&ctx,key.data());
        res.resize((data.size()/SM4_BLOCK_SIZE+1)*SM4_BLOCK_SIZE);
        size_t outlen = 0;
        if(sm4_ecb_encrypt_update(&ctx,data.data(),data.size(),res.data(),&outlen) != 1 || sm4_ecb_encrypt_finish(&ctx,data.data(),&outlen)!=1){
            error_print();
            res.clear();
        }
        return std::vector<uint8_t>(res.begin(),res.begin()+outlen);
    }
    static std::vector<uint8_t> DecryptECBPadding(const std::vector<uint8_t>&  key,std::vector<uint8_t>& data){
        static SM4_ECB_CTX ctx;
        std::vector<uint8_t> res;
        if(key.size() != SM4_BLOCK_SIZE){
            return res;
        }
        sm4_ecb_decrypt_init(&ctx,key.data());
        res.resize((data.size()/SM4_BLOCK_SIZE+1)*SM4_BLOCK_SIZE);
        size_t outlen = 0;
        if(sm4_ecb_decrypt_update(&ctx,data.data(),data.size(),res.data(),&outlen) != 1 || sm4_ecb_decrypt_finish(&ctx,data.data(),&outlen)!=1){
            error_print();
            res.clear();
        }
        return std::vector<uint8_t>(res.begin(),res.begin()+outlen);
    }
    };
    
}

#endif