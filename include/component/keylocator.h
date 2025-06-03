#ifndef KEYLOCATOR_H_
#define KEYLOCATOR_H_

#include "identifier.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include <memory>

namespace mindev::component{
    class KeyLocator:public mindev::encoding::IEncodingAble,public TlvComponentBase,public TemplateInit{
public:
    typedef std::shared_ptr<KeyLocator> ptr;
    KeyLocator(){};
    template<typename T>
    friend std::optional<KeyLocator> BuildKeyLocator(T&& val){
        using ParamType = std::conditional_t<std::is_scalar_v<std::decay_t<T>>, std::decay_t<T>, const std::decay_t<T>&>;
        const ParamType value = std::forward<T>(val);
        KeyLocator res;
        if constexpr (std::is_same_v<std::decay_t<decltype(value)>, mindev::encoding::Block>){
            if(!res.WireDecode(value)){
                return std::nullopt;
            };
            return res;
        }else if constexpr(std::is_same_v<std::decay_t<decltype(value)>, std::string>){
            auto tmp =  Identifier::BuildIdentifierByString(value);
            if(!tmp.has_value()){
                return std::nullopt;
            }
            res.identifier = tmp.value();
            return res;
        }else if constexpr(std::is_same_v<std::decay_t<decltype(value)>, IdentifierComponentContainer>){
            auto tmp =  Identifier::BuildIdentifierByComponents(value);
            if(!tmp.has_value()){
                return std::nullopt;
            }
            res.identifier = tmp.value();
            return res;
        }else if constexpr(std::is_same_v<std::decay_t<decltype(value)>, Identifier>){
            auto tmp =  Identifier::BuildIdentifierByComponents(value.GetComponents());
            if(!tmp.has_value()){
                return std::nullopt;
            }
            res.identifier = tmp.value();
            return res;
        }else{
            static_assert(always_false<T>,"unsported type to init !");
        }
    }
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    inline bool IsValid(){return this->identifier.IsValid();};
    inline Identifier& GetIdentifier(){return this->identifier;}
private:
    Identifier identifier;
    
    };
}

#endif
