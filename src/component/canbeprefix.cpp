#include "mindev/include/component/canbeprefix.h"

namespace mindev::component{
    int CanBePrefix::WireEncode(mindev::encoding::Encoder& encoder){
        if(!this->canBePrefix){
            return 0;
        }
        int totalLength = 0;
        auto tmp1 = mindev::encoding::VlInt(totalLength);
        int tmpLen = encoder.PrependVarNumber(tmp1);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;
        auto tmp2 = mindev::encoding::VlInt(mindev::encoding::TLV::TlvCanBePrefix);
        tmpLen = encoder.PrependVarNumber(tmp2);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool CanBePrefix::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvCanBePrefix))){
            return false;
        }
        this->canBePrefix = true;
        this->doInitial();
        return true;
    }
}