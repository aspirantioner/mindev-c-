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
    mindev::component::Identifier identifier = mindev::component::Identifier();
    mindev::encoding::VlInt tlvType = mindev::encoding::VlInt(mindev::encoding::TLV::TlvInvalid);
public:
    inline mindev::encoding::VlInt GetTlvType(){
        return this->tlvType;
    }
    inline  bool IsValid(){return mindev::encoding::TLV::IsValidIdentifierType(this->tlvType);};
    IdentifierWrapper(){}
    template<typename... Args>
    IdentifierWrapper(Args... args){
        constexpr  size_t N = sizeof...(Args);
        if constexpr (N == 1){
            auto&& [block] = std::forward_as_tuple(std::forward<Args>(args)...);
            if constexpr (std::is_same_v<std::decay_t<decltype(block)>, mindev::encoding::Block>){
                if(block.ParseSubElements()){
                    auto tmp = block.GetSubElements().GetBlock(0);
                    if(tmp.has_value()){
                        auto value = Identifier::BuildIdentifierByBlock(tmp.value());
                        if(value.has_value()){
                            this->tlvType = block.GetType();
                            this->identifier = value.value(); 
                        }
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
    template<typename>
    inline static constexpr bool always_false = false;
    template<typename T>
    friend IdentifierWrapper BuildIdentifierWrapper(T&& val,decltype(mindev::encoding::TLV::TlvInvalid) flag){
        using ParamType = std::conditional_t<std::is_scalar_v<std::decay_t<T>>, std::decay_t<T>, const std::decay_t<T>&>;
        const ParamType value = std::forward<T>(val);
        IdentifierWrapper res;
        if constexpr(std::is_same_v<ParamType,const std::string&>){
            res.tlvType = mindev::encoding::VlInt(flag);
            auto tmp = Identifier::BuildIdentifierByString(value);
            if(tmp.has_value()){
                res.identifier = tmp.value();
            }
        }else if constexpr(std::is_same_v<ParamType,const IdentifierComponentContainer&>){
            res.tlvType = mindev::encoding::VlInt(flag);
            auto tmp = Identifier::BuildIdentifierByComponents(value);
            if(tmp.has_value()){
                res.identifier = tmp.value();
            }
        }else if constexpr(std::is_same_v<ParamType,const mindev::encoding::Block&>){
            res.tlvType = mindev::encoding::VlInt(flag);
            auto tmp = Identifier::BuildIdentifierByBlock(value);
            if(tmp.has_value()){
                res.identifier = tmp.value();
            }
        }else{
            static_assert(always_false<T>, "this type unsupport!");
        }
        return res;
    }
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    inline std::string ToUri()  {
        return this->identifier.ToUri();
    }
    inline Identifier& GetIdentifier(){return this->identifier;}
    };
}

#endif
