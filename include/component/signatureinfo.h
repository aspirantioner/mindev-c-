
#ifndef SIGNATUREINFO_H_
#define SIGNATUREINFO_H_

#include "tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
#include "signaturetype.h"
#include "keylocator.h"

namespace mindev::component{

    template<typename T>
    std::optional<SignatureType> BuildSignatureType(T&& val);
    
    template<typename T>
    std::optional<KeyLocator> BuildKeyLocator(T&& val);

    class SignatureInfo:public TlvComponentBase,public mindev::encoding::IEncodingAble,public TemplateInit {
public:    
    typedef std::shared_ptr<SignatureInfo> ptr;
    SignatureInfo(){}
    
    template<typename... Args>
    friend std::optional<SignatureInfo> BuildSignatureInfo(Args... args){
        constexpr  size_t N = sizeof...(Args);
        SignatureInfo res;
        if constexpr (N == 1){
            auto&& [block] = std::forward_as_tuple(std::forward<Args>(args)...);
            if constexpr (std::is_same_v<std::decay_t<decltype(block)>, SignatureAlgorithm>){
                auto val = BuildSignatureType(block);
                if(!val.has_value()){
                    return std::nullopt;
                }
                res.signatureType = val.value();
                return res;
            }else if constexpr(std::is_same_v<std::decay_t<decltype(block)>, mindev::encoding::Block>){
                if(!res.WireDecode(block)){
                    return std::nullopt;
                }
                return res;
            }else{
                static_assert(always_false<std::decay_t<decltype(block)>>, "this type unsupport!");
            }
        }else if constexpr(N == 2){
            auto&& [tlvType,varType] = std::forward_as_tuple(std::forward<Args>(args)...);
        
            if constexpr(std::is_same_v<std::decay_t<decltype(tlvType)>, SignatureAlgorithm> && std::is_same_v<std::decay_t<decltype(tlvType)>, KeyLocator>){
                auto val = BuildSignatureType(tlvType);
                if(!val.has_value()){
                    return std::nullopt;
                }
                res.signatureType = val.value();     
                
                val = BuildKeyLocator(varType.GetIdentifier);
                if(!val.has_value()){
                    return std::nullopt;
                }
                res.keyLocator = val.value();  
                
                return res;
            }else{
                static_assert(always_false<decltype(tlvType)>, "this type unsupport!");
            }
        }else{
            static_assert(always_false<Args...>, "this type unsupport!");
        }
    }
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    SignatureType signatureType;
    KeyLocator keyLocator;
    };
}

#endif
