#ifndef KEYUTILS_H_
#define KEYUTILS_H_

#include "mindev/include/minsecurity/common.h"
#include "mindev/include/minsecurity/crypto/publickeyinterface.h"
#include "mindev/include/minsecurity/crypto/sm2/sm2privatekey.h"
#include "mindev/include/minsecurity/crypto/sm2/sm2publickey.h"
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
    static std::vector<char> Get16BytePasswd(const std::vector<char>& passwd){
        
    }
    };
}


#endif