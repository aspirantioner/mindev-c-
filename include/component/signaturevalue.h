
#ifndef SIGNATUREVALUE_H_
#define SIGNATUREVALUE_H_

#include "mindev/include/common/templateinit.h"
#include "tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

#include <vector>

namespace mindev::component{
    class SignatureValue:public TlvComponentBase,public mindev::encoding::IEncodingAble,public TemplateInit{
public:
    typedef std::shared_ptr<SignatureValue> ptr;
    SignatureValue(){}
    template<typename T>
    friend std::optional<SignatureValue> BuildSignatureValue(T&& val){
        using ParamType = std::conditional_t<std::is_scalar_v<std::decay_t<T>>, std::decay_t<T>, std::decay_t<T>&>;
        const ParamType value = std::forward<T>(val);
        SignatureValue res;
        if constexpr (std::is_same_v<std::decay_t<decltype(value)>, mindev::encoding::Block>){
            if(!res.WireDecode(value)){
                return std::nullopt;
            };
            return res;
        }else if constexpr(std::is_same_v<std::decay_t<decltype(value)>, std::vector<char>>){
            res.value = val;
            return res;
        }else{
            static_assert(always_false<T>,"unsported type to init !");
        }
    }
    std::vector<char>& GetValue(){return this->value;}
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    std::vector<char> value;
    };
}

#endif
