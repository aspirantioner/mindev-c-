#ifndef PRIVATEKEYINTERFACE_H_
#define PRIVATEKEYINTERFACE_H_

#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "thirdparty/GmSSL/include/gmssl/sm2.h"
#ifdef __cplusplus
}
#endif

#include <vector>
namespace mindev::minsecurity::crypto {
    class PublicKeyInterface {
public:
    typedef std::shared_ptr<PublicKeyInterface> ptr; 
    virtual std::vector<char> GetBytes()const{return std::vector<char>();}
    virtual void SetSm2Key(std::shared_ptr<SM2_KEY> ptr){return;}
    virtual std::vector<char> Encrypt(const std::vector<char>& content){return std::vector<char>();}
    bool Verify(const std::vector<char>& content,const std::vector<char>& digest)const{return true;}
    };
}


#endif