#ifndef KEYUTILS_H_
#define KEYUTILS_H_

#include "mindev/include/minsecurity/common.h"
#include "mindev/include/minsecurity/crypto/hashalgo.h"
#include "mindev/include/minsecurity/crypto/publickeyinterface.h"
#include "mindev/include/minsecurity/crypto/sm2/sm2privatekey.h"
#include "mindev/include/minsecurity/crypto/sm2/sm2publickey.h"
#include <cstdint>
#include <optional>
#include <vector>
namespace mindev::minsecurity::crypto {
    class KeyUtils {
public:
    static std::optional<PublicKeyInterface> UnMarshalPublicKey(std::shared_ptr<SM2_KEY> ptr,int algorithm){
        switch(algorithm){
            case static_cast<int>(mindev::minsecurity::Common::PublicKeyAlgorithm::SM2):
                mindev::minsecurity::crypto::sm2::SM2PublicKey sm2PublicKey(ptr);
                return sm2PublicKey;
        }
        return std::nullopt;
    }
    static std::optional<PrivateKeyInterface> UnMarshalPrivateKey(std::shared_ptr<SM2_KEY> ptr,int algorithm){
        switch(algorithm){
            case static_cast<int>(mindev::minsecurity::Common::PublicKeyAlgorithm::SM2):
                mindev::minsecurity::crypto::sm2::SM2PrivateKey sm2PrivateKey(ptr);
                return sm2PrivateKey;
        }
        return std::nullopt;
    }
    static std::vector<uint8_t> Get16BytePasswd(std::vector<uint8_t>& passwd){
        auto res = HashAlgo::Sm3(passwd);
        if(res.size() == 32){
            for(int i = 0;i<16;i++){
                res[i] += res[i+16];
            }
        }
        return std::vector<uint8_t>(res.begin(),res.begin()+16);
    }
    };
}


#endif