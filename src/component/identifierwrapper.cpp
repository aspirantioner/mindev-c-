#include "mindev/include/component/identifierwrapper.h"

namespace mindev::component{
    template<typename>
    inline constexpr bool always_false = false;

    template<typename T>
    IdentifierWrapper BuildIdentifierWrapper(T&& val,decltype(mindev::encoding::TLV::TlvInvalid) flag){
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
    }
    int IdentifierWrapper::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        int tmpLen = this->identifier.WireEncode(encoder);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;
    
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
    
        tmpLen = encoder.PrependVarNumber(this->tlvType);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool IdentifierWrapper::WireDecode(mindev::encoding::Block& block){
        if(mindev::encoding::TLV::IsValidIdentifierType(block.GetType())){
            return false;
        }
        if(!block.ParseSubElements()){
            return false;
        }
        if(block.GetSubElements().Length()!=1){
            return false;
        }
        auto val = Identifier::BuildIdentifierByBlock(block);
        if(!val.has_value()){
            return false;
        }
        this->identifier = val.value();
        this->tlvType = block.GetType();
        return true;
    }
}
