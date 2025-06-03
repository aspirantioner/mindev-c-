#ifndef IDENTIFIERWRAPPER_H_
#define IDENTIFIERWRAPPER_H_

#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/block.h"
#include "mindev/include/encoding/iencodingable.h"
#include "mindev/include/component/identifier.h"
#include "mindev/include/encoding/tlv.h"

namespace mindev::component{
    class IdentifierWrapper:public TlvComponentBase,public mindev::encoding::IEncodingAble,public TemplateInit{
private:
    Identifier identifier = Identifier();
    mindev::encoding::VlInt tlvType = mindev::encoding::VlInt(mindev::encoding::TLV::TlvInvalid);
public:
    inline const mindev::encoding::VlInt GetTlvType(){
        return this->tlvType;
    }
    inline  bool IsValid(){return mindev::encoding::TLV::IsValidIdentifierType(this->tlvType);};
    template<typename... Args>
    IdentifierWrapper(Args... args){
        constexpr  size_t N = sizeof...(Args);
        if constexpr (N == 1){
            auto&& [block] = std::forward_as_tuple(std::forward<Args>(args)...);
            if constexpr (std::is_same_v<std::decay_t<decltype(block)>, mindev::encoding::Block>){
                if(block.ParseSubElements()){
                    auto value = Identifier::BuildIdentifierByBlock(block.GetSubElements().GetBlock(0));
                    if(value.has_value()){
                        this->tlvType = block.GetType();
                        this->identifier = value.value(); 
                    }
                }
            }else{
                static_assert(always_false<std::decay_t<decltype(block)>>, "this type unsupport!");
            }
        }else if constexpr(N == 2){
            auto&& [tlvType,varType] = std::forward_as_tuple(std::forward<Args>(args)...);
        
            if constexpr(std::is_same_v<std::decay_t<decltype(tlvType)>, mindev::encoding::VlInt>){
                if constexpr(std::is_same_v<std::decay_t<decltype(varType)>,Identifier>){
                    if(mindev::encoding::TLV::IsValidIdentifierType(tlvType)){
                        this->tlvType = tlvType;
                        this->identifier = varType;
                    }
                } else if constexpr(std::is_same_v<std::decay_t<decltype(varType)>,std::string>){
                    if(mindev::encoding::TLV::IsValidIdentifierType(tlvType)){
                        auto value = Identifier::BuildIdentifierByString(varType);
                        if(value.has_value()){
                            this->tlvType = tlvType;
                            this->identifier = value.value();
                        }
                    }
                } else if constexpr(std::is_same_v<std::decay_t<decltype(varType)>,IdentifierComponentContainer>){
                    if(mindev::encoding::TLV::IsValidIdentifierType(tlvType)){
                        auto value = Identifier::BuildIdentifierByComponents(varType);
                        if(value.has_value()){  
                            this->tlvType = tlvType;
                            this->identifier = value.value();
                        }
                    }
                }else if constexpr(std::is_same_v<std::decay_t<decltype(varType)>,mindev::encoding::Block>){
                    if(mindev::encoding::TLV::IsValidIdentifierType(tlvType)){
                        auto value = Identifier::BuildIdentifierByBlock(varType);
                        if(value.has_value()){
                            this->tlvType = tlvType;
                            this->identifier = value.value();
                        }
                    }
                }else {
                    static_assert(always_false<decltype(tlvType)>, "this type unsupport!");
                }
            }else{
                static_assert(always_false<decltype(tlvType)>, "this type unsupport!");
            }
        }else{
            static_assert(always_false<Args...>, "this type unsupport!");
        }
    }
    template<typename T>
    friend  IdentifierWrapper BuildIdentifierWrapper(T&& val,decltype(mindev::encoding::TLV::TlvInvalid) flag);
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    inline std::string ToUri()  {
        return this->identifier.ToUri();
    }
    };
}

#endif
