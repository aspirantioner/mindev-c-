#include "mindev/include/component/identifiercomponentcontainer.h"

namespace mindev::component{
    int IdentifierComponentContainer::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        std::vector<char> vec(this->value.begin(),this->value.end());
        int tmpLen = encoder.PrependByteArray(vec,mindev::encoding::SizeT(vec.size()));
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
    bool IdentifierComponentContainer::WireDecode(mindev::encoding::Block& block){
        this->tlvType = block.GetType();
        this->SetValue(std::string(block.GetValue().begin(),block.GetValue().end()));
        return true;
    }
    std::optional<IdentifierComponentContainer> IdentifierComponentContainer::GetPrefix(int num){
        if(num>this->Length()){
            return std::nullopt;
        }
        IdentifierComponentContainer res;
        for(int i = 0;i<num;i++){
            res.AddElement(this->GetIdentifierComponents()[i]);
        }
        return res;
    }
    std::optional<IdentifierComponentContainer> IdentifierComponentContainer::GetSubIdentifierContainer(int startIndex,int num){
        if(startIndex+num>this->Length()){
            return std::nullopt;
        }
        IdentifierComponentContainer res;
        for(int i = startIndex;i<startIndex+num;i++){
            res.AddElement(this->GetIdentifierComponents()[i]);
        }
        return res;
    }
}
