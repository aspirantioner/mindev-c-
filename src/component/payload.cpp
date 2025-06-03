#include "mindev/include/component/payload.h"

namespace mindev::component{
    int Payload::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        int tmpLen = encoder.PrependByteArray(this->value,mindev::encoding::SizeT(this->value.size()));
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvPayload);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool Payload::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(),mindev::encoding::VlInt(mindev::encoding::TLV::TlvPayload))){
            return false;
        }
        this->SetValue(block.GetValue());
        return true;
    }
}
