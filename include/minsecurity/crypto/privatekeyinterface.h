#ifndef PUBLICKEYINTERFACE_H_
#define PUBLICKEYINTERFACE_H_

#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "thirdparty/GmSSL/include/gmssl/sm2.h"
#ifdef __cplusplus
}
#endif

// #include "thirdparty/GmSSL/include/gmssl/sm2.h"
#include <vector>
namespace mindev::minsecurity::crypto {
    class PrivateKeyInterface {
public:
    virtual std::vector<char> GetBytes()const{return std::vector<char>();}
    virtual void SetSm2key(std::shared_ptr<SM2_KEY> ptr){return;}
    //virtual bool SetBytes(const std::vector<char>& bytes){return true;}
    virtual std::vector<char> Decrypt(const std::vector<char>& cipher){return std::vector<char>();}
    virtual std::vector<char> Sign(const std::vector<char>& content)const{return std::vector<char>();}
    };
}


#endif