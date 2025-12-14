#include "mindev/include/component/lppacketfragmentseq.h"

namespace mindev::component{
    int LpPacketFragmentSeq::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;

        int tmpLen = encoder.PrependNonNegativeInteger(this->fragmentSeq);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvLpPacketFragmentSeq);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool LpPacketFragmentSeq::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvLpPacketFragmentSeq))){
            return false;
        }
        long value = mindev::encoding::TLV::ReadNonNegativeInteger(block.GetValue(), 0,bigint::_bigint_to<int>(block.GetLength().GetVlIntValue()));
        if(value<0){
            return false;
        }
        this->SetFragmentSeq(value);
        return true;
    }
}
