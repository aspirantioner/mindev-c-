#include "mindev/include/component/controlparametercount.h"

namespace mindev::component{
    int ControlParameterCount::WireEncode(mindev::encoding::Encoder& encoder){
        int totalLength = 0;
        int tmpLen = encoder.PrependNonNegativeInteger(this->count);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvManagementCount);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool ControlParameterCount::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementCount))){
            return false;
        }
        auto value = mindev::encoding::TLV::ReadNonNegativeInteger(block.GetValue(), 0, bigint::_bigint_to<int>(block.GetLength().GetVlIntValue()));
        if(value<0){
            return false;
        }
        this->SetCount(value);
        return true;
    }
}