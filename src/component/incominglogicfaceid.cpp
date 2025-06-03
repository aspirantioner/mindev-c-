#include "mindev/include/component/incominglogicfaceid.h"

namespace mindev::component{
    int IncomingLogicFaceId::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        int tmpLen = encoder.PrependNonNegativeInteger(this->incomingLogicFaceId);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvIncomingLogicFaceId);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool IncomingLogicFaceId::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetValue(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvIncomingLogicFaceId))){
            return false;
        }
        long value = mindev::encoding::TLV::ReadNonNegativeInteger(block.GetValue(), 0, bigint::_bigint_to<int>(block.GetLength().GetVlIntValue()));
        if(value<0){
            return false;
        }
        this->SetIncomingLogicFaceId(value);
        return true;
    }
}
