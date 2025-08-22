#ifndef HASHALGO_H_
#define HASHALGO_H_

#include "thirdparty/GmSSL/include/gmssl/sm3.h"
#include <cstdint>
#include <optional>
#include <vector>
namespace mindev::minsecurity::crypto {
    class HashAlgo {
public:
    static std::vector<uint8_t> Sm3(std::vector<uint8_t>& content){
        std::vector<uint8_t> res;
        res.resize(32,0);
        SM3_CTX sm3_ctx;
        sm3_init(&sm3_ctx);
        sm3_update(&sm3_ctx, content.data(), content.size());
        sm3_finish(&sm3_ctx, res.data());
    }
    };
}


#endif