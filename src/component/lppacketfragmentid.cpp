#include "mindev/include/component/lppacketfragmentid.h"

namespace mindev::component{
    int LpPacketFragmentId::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;

        int tmpLen = encoder.PrependNonNegativeInteger(this->id);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvLpPacketFragmentId);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool LpPacketFragmentId::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvLpPacketFragmentId))){
            return false;
        }
        long value = mindev::encoding::TLV::ReadNonNegativeInteger(block.GetValue(), 0,bigint::_bigint_to<int>(block.GetLength().GetVlIntValue()));
        if(value<0){
            return false;
        }
        this->SetId(value);
        return true;
    }
}
