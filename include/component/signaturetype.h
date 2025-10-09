#ifndef SIGNATURETYPE_H_
#define SIGNATURETYPE_H_

#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
#include "signaturealgorithm.h"
#include "mindev/include/common/templateinit.h"
#include "mindev/include/minsecurity/common.h"
#include <optional>

namespace mindev::component{
    class SignatureType:public TemplateInit,public TlvComponentBase,public mindev::encoding::IEncodingAble{
private:
    SignatureAlgorithm value; // SignatureAlgorithm

public: 
    
    typedef std::shared_ptr<SignatureType> ptr;
    SignatureType(){}
    
    template<typename T>
    friend std::optional<SignatureType> BuildSignatureType(T&& val){
        using ParamType = std::conditional_t<std::is_scalar_v<std::decay_t<T>>, std::decay_t<T>, const std::decay_t<T>&>;
        const ParamType value = std::forward<T>(val);
        SignatureType res;
        if constexpr (std::is_same_v<std::decay_t<decltype(value)>, mindev::encoding::Block>){
            if(!res.WireDecode(value)){
                return std::nullopt;
            };
            return res;
        }else if constexpr(std::is_same_v<std::decay_t<decltype(value)>, SignatureAlgorithm>){
            if(val.GetSignatureAlgorithm()!=(int)mindev::minsecurity::Common::SignatureAlgorithm::SM3withSM2){
                return std::nullopt;
            }
            res.value = val;
            return res;
        }else{
            static_assert(always_false<T>,"unsported type to init !");
        }
    }
    
    inline SignatureAlgorithm GetValue(){return this->value;}
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
