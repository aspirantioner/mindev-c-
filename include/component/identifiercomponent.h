#ifndef IDENTIFIERCOMPONENT_H_
#define IDENTIFIERCOMPONENT_H_
#include "mindev/include/common/stringutils.h"
#include "mindev/include/encoding/iencodingable.h"
#include "mindev/include/encoding/block.h"
#include "tlvcomponentbase.h"
#include <cstdint>

namespace mindev::component{
    class IdentifierComponent:public TemplateInit,public mindev::encoding::IEncodingAble,public TlvComponentBase{
private:
    mindev::encoding::Block identifierBlock;    
    uint8_t marker = MarkerInvalid;
    std::string stringValue;
    long intValue;
    std::vector<char> byteArrayValue;
    static const uint8_t MarkerString = 0x00;
    static const uint8_t MarkerNonNegativeInteger = 0x01;
    static const uint8_t MarkerByteArray = 0x02;
    static const uint8_t MarkerVersionNumber = 0x03;
    static const uint8_t MarkerFragmentNumber = 0x04;
    static const uint8_t MarkerInvalid = 0xff;
    inline bool IsInMarker(uint8_t marker)const{return marker>=MarkerString && marker<=MarkerFragmentNumber;};
    
public:
    IdentifierComponent(){};
//     IdentifierComponent(const IdentifierComponent&) = default;
//     IdentifierComponent(IdentifierComponent&&) noexcept = default;
//     IdentifierComponent& operator=(const IdentifierComponent&) = default;
//     IdentifierComponent& operator=(IdentifierComponent&&) noexcept = default;
    template<typename T, std::enable_if_t<!std::is_same_v<std::decay_t<T>, IdentifierComponent>, int> = 0>
    explicit IdentifierComponent(T&& val) {
        using ParamType = std::conditional_t<std::is_scalar_v<std::decay_t<T>>, std::decay_t<T>, const std::decay_t<T>&>;
        const ParamType value = std::forward<T>(val);
        
        if constexpr(std::is_same_v<ParamType,const std::string&>){
            this->identifierBlock.SetType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifierComponent));
            int len = value.size();
            this->identifierBlock.SetLength(mindev::encoding::VlInt(len+1));
            std::vector<char> tmp(len+1);
            tmp[0] = MarkerString;
            std::copy(value.begin(),value.end(),tmp.begin()+1);
            this->identifierBlock.SetValue(tmp);
            this->marker = MarkerString;
            this->stringValue = value; 
        }else if constexpr(std::is_same_v<ParamType,long>){
            this->identifierBlock.SetType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifierComponent));
            auto uint64Array =  mindev::encoding::Encoder::BuildNonNegativeIntegerArr(value);
            this->identifierBlock.SetLength(mindev::encoding::VlInt(uint64Array.size()+1));
            std::vector<char> tmp(uint64Array.size()+1);
            tmp[0] = MarkerNonNegativeInteger;
            std::copy(uint64Array.begin(),uint64Array.end(),tmp.begin()+1);
            this->identifierBlock.SetValue(tmp);
            this->marker = MarkerNonNegativeInteger;
            this->intValue = value; 
        }else if constexpr(std::is_same_v<ParamType,const std::vector<char>&>){
            this->identifierBlock.SetType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifierComponent));
            this->identifierBlock.SetLength(mindev::encoding::VlInt(value.size()+1));
            std::vector<char> tmp(value.size()+1);
            tmp[0] = MarkerByteArray;
            std::copy(value.begin(),value.end(),tmp.begin()+1);
            this->identifierBlock.SetValue(tmp);
            this->marker = MarkerByteArray;
            this->byteArrayValue = value; 
        }else{
            static_assert(always_false<T>,"unsported type to init !");
        }
    };
    inline bool IsString(){return this->marker = MarkerString;};
    inline bool IsNonNegativeInteger(){return this->marker = MarkerNonNegativeInteger;};
    inline bool IsByteArray(){return this->marker = MarkerByteArray;};
    inline bool IsVersionNumber(){return this->marker = MarkerVersionNumber;};
    inline bool IsFragmentNumber(){return this->marker = MarkerFragmentNumber;};
    friend  IdentifierComponent BuildIdentifierComponentByVersionNumber(long versionNumber);
    friend  IdentifierComponent BuildIdentifierComponentByFragmentNumber(long FragmentNumber);
    friend IdentifierComponent BuildIdentifierComponentByBlock(mindev::encoding::Block& block);
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    bool IsValid(){return IsInMarker(this->marker);};
    inline uint8_t GetMarker()const{return this->marker;};
    inline mindev::encoding::Block& GetBlock(){return this->identifierBlock;};
    inline std::string& GetString(){return this->stringValue;};
    inline long GetNonNegativeInteger()const{return this->intValue;};
    inline long GetVersionNumber()const{return this->intValue;};
    inline long GetFragmentNumber()const{return this->intValue;}
    inline std::vector<char>& GetByteArray(){return this->byteArrayValue;};
    inline bool IsString()const{return this->marker == MarkerString;};
    inline bool IsNonNegativeInteger()const{return this->marker == MarkerNonNegativeInteger;};
    inline bool IsByteArray()const{return this->marker == MarkerByteArray;};
    inline bool IsVersionNumber()const{return this->marker == MarkerVersionNumber;};
    inline bool IsFragmentNumber()const{return this->marker == MarkerFragmentNumber;};
    bool operator == (const IdentifierComponent& target) const{
        if(this->marker == target.marker){
            if(this->IsString()){
                return this->stringValue == target.stringValue;
            }
            else if((this->IsNonNegativeInteger() && target.IsNonNegativeInteger())||(this->IsVersionNumber()&&
                target.IsVersionNumber()) || (this->IsFragmentNumber() && target.IsFragmentNumber())){
                return this->intValue == target.intValue;    
            }
            else if(this->IsByteArray()){
                return this->byteArrayValue == target.byteArrayValue;
            }    
        }
        return false;
    }
    inline std::string ToUri()const{
        if(this->IsString()){
            return stringutils::Escape(this->stringValue);    
        }
        else if(this->IsByteArray()){
            return stringutils::Escape(std::string(this->byteArrayValue.begin(),this->byteArrayValue.end()));
        }else{
            return std::to_string(this->intValue);
        }
    }
    inline std::string ToUriTemp()const{
        if(this->IsString()){
            return this->stringValue;    
        }
        else if(this->IsByteArray()){
            return std::string(this->byteArrayValue.begin(),this->byteArrayValue.end());
        }else{
            return std::to_string(this->intValue);
        }
    }
    inline std::string ToString()const{
        std::string res;
        res.push_back(this->marker);
        return res+this->ToUriTemp();
    }
    };
}

#endif
