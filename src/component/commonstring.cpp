#include "mindev/include/component/commonstring.h"

namespace mindev::component{
    int CommonString::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        std::vector<char> vec(this->value.begin(),this->value.end());
        auto tmp1 = mindev::encoding::SizeT(vec.size());
        int tmpLen = encoder.PrependByteArray(vec,tmp1);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;
        auto tmp2 = mindev::encoding::VlInt(totalLength);
        tmpLen = encoder.PrependVarNumber(tmp2);
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
    bool CommonString::WireDecode(mindev::encoding::Block& block){
        this->tlvType = block.GetType();
        this->SetValue(std::string(block.GetValue().begin(),block.GetValue().end()));
        return true;
    }
}