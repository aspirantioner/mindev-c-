#include "mindev/include/component/identifiercomponent.h"

namespace mindev::component{
    IdentifierComponent BuildIdentifierComponentByVersionNumber(long versionNumber){
        IdentifierComponent res;
        res.identifierBlock.SetType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifierComponent));
        auto len = mindev::encoding::TLV::SizeOfNonNegativeInteger(versionNumber)+1;
        res.identifierBlock.SetLength(mindev::encoding::VlInt(len));
        std::vector<char> tmp1(len);
        tmp1[0] = IdentifierComponent::MarkerVersionNumber;
        res.marker = IdentifierComponent::MarkerVersionNumber;
        auto tmp2 = mindev::encoding::Encoder::BuildNonNegativeIntegerArr(versionNumber);
        std::copy(tmp2.begin(),tmp2.end(),tmp1.begin()+1);
        res.identifierBlock.SetValue(tmp1);
        res.intValue = versionNumber;
        return res;
    }
    IdentifierComponent BuildIdentifierComponentByFragmentNumber(long fragmentNumber){
        IdentifierComponent res;
        res.identifierBlock.SetType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifierComponent));
        auto len = mindev::encoding::TLV::SizeOfNonNegativeInteger(fragmentNumber)+1;
        res.identifierBlock.SetLength(mindev::encoding::VlInt(len));
        std::vector<char> tmp1(len);
        tmp1[0] = IdentifierComponent::MarkerFragmentNumber;
        res.marker = IdentifierComponent::MarkerFragmentNumber;
        auto tmp2 = mindev::encoding::Encoder::BuildNonNegativeIntegerArr(fragmentNumber);
        std::copy(tmp1.begin()+1,tmp1.end(),tmp2.begin());
        res.identifierBlock.SetValue(tmp1);
        res.intValue = fragmentNumber;
        return res;
    }
    IdentifierComponent BuildIdentifierComponentByBlock(mindev::encoding::Block& block){
        IdentifierComponent res;
        res.WireDecode(block);
        return res;
    }
    int IdentifierComponent::WireEncode(mindev::encoding::Encoder& encoder){
        return this->identifierBlock.Encode(encoder);
    }
    bool IdentifierComponent::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifierComponent))){
            return false;
        }
        this->identifierBlock = mindev::encoding::Block(block);
        auto length = bigint::_bigint_to<int>(this->identifierBlock.GetLength().GetVlIntValue());
        std::vector<char> value = this->identifierBlock.GetValue();
        if(length<1){
            return false;
        }
        this->marker = value[0];
        
        if(IsString()){
            this->stringValue = std::string(value.begin()+1,value.end());
        }else if(IsNonNegativeInteger() || IsVersionNumber() || IsFragmentNumber()){
            auto res = mindev::encoding::TLV::ReadNonNegativeInteger(value, 1, length);
            if(res==-1){
                return false;
            }
            this->intValue = res;    
        }else{
            this->byteArrayValue = std::vector<char>(value.begin()+1,value.end());
        }
        return true;
    }
}
