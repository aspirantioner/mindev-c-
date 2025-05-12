#include "mindev/include/component/controlparametermtu.h"

namespace mindev::component{
    int ControlParameterMtu::WireEncode(mindev::encoding::Encoder& encoder){
        int totalLength = 0;
        int tmpLen = encoder.PrependNonNegativeInteger(this->mtu);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvManagementMtu);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool ControlParameterMtu::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementMtu))){
            return false;
        }
        auto value = mindev::encoding::TLV::ReadNonNegativeInteger(block.GetValue(), 0, bigint::_bigint_to<int>(block.GetLength().GetVlIntValue()));
        if(value<0){
            return false;
        }
        this->SetMtu(value);
        return true;
    }
}
