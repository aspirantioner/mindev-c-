#include "mindev/include/payload.h"

namespace mindev::component{
    int Payload::WireEncode(mindev::encoding::Encoder& encoder){
        
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
    bool Payload::WireDecode(mindev::encoding::Block& block){
        this->tlvType = block.GetType();
        this->SetValue(std::string(block.GetValue().begin(),block.GetValue().end()));
        return true;
    }
}
