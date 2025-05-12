#include "mindev/include/component/canbeprefix.h"

namespace mindev::component{
    int CanBePrefix::WireEncode(mindev::encoding::Encoder& encoder){
        if(!this->canBePrefix){
            return 0;
        }
        int totalLength = 0;
        int tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(mindev::encoding::TLV::TlvCanBePrefix));
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