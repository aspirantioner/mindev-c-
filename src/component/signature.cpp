#include "mindev/include/component/signature.h"
#include "mindev/include/component/keylocator.h"

namespace mindev::component{
    template<typename T>
    std::optional<KeyLocator> BuildKeyLocator(T&& val);
    template<typename... Args>
    std::optional<SignatureInfo> BuildSignatureInfo(Args... args);
    template<typename T>
    std::optional<SignatureValue> BuildSignatureValue(T&& val);

    Signature::Signature(const mindev::minsecurity::identity::Identity& identity,std::vector<uint8_t>& value){
        auto res = BuildKeyLocator(identity.GetName());        
        if(res.has_value()){
            SignatureAlgorithm signature_algorithm = SignatureAlgorithm(identity.GetKeyParam().SignatureAlgorithm);
            KeyLocator keylactor = res.value();
            auto info = BuildSignatureInfo(signature_algorithm,keylactor);
            if(info.has_value()){
                this->sigInfo = info.value();
                auto tmp = byteutils::Uint8ToChar(value);
                auto vec = BuildSignatureValue(tmp);
                if(vec.has_value()){
                    this->sigValue = vec.value();
                }
            }
        }
    }
}
