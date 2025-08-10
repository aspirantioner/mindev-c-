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
    static std::optional<PublicKeyInterface> UnMarshalPublicKey(const std::vector<char>& bytesOfPublicKey,int algorithm){
        if(bytesOfPublicKey.size() == 0){
            return std::nullopt;
        }
        switch(algorithm){
            case static_cast<int>(mindev::minsecurity::Common::PublicKeyAlgorithm::SM2):
                mindev::minsecurity::crypto::sm2::SM2PublicKey sm2PublicKey;
                sm2PublicKey.SetBytes(bytesOfPublicKey);
                return sm2PublicKey;
        }
        return std::nullopt;
    }
    static std::optional<PrivateKeyInterface> UnMarshalPrivateKey(const std::vector<char>& bytesOfPrivateKey,int algorithm){
        if(bytesOfPrivateKey.size() == 0){
            return std::nullopt;
        }
        switch(algorithm){
            case static_cast<int>(mindev::minsecurity::Common::PublicKeyAlgorithm::SM2):
                mindev::minsecurity::crypto::sm2::SM2PrivateKey sm2PrivateKey;
                sm2PrivateKey.SetBytes(bytesOfPrivateKey);
                return sm2PrivateKey;
        }
        return std::nullopt;
    }
    static std::vector<char> Get16BytePasswd(const std::vector<char>& passwd){
        
    }
    };
}


#endif