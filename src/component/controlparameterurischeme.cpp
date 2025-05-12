#include "mindev/include/component/controlparameterurischeme.h"

namespace mindev::component{
    int ControlParameterUriScheme::WireEncode(mindev::encoding::Encoder& encoder){
        int totalLength = 0;
        int tmpLen = encoder.PrependNonNegativeInteger(this->uriScheme);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvManagementUriScheme);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool ControlParameterUriScheme::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementUriScheme))){
            return false;
        }
        auto value = mindev::encoding::TLV::ReadNonNegativeInteger(block.GetValue(), 0, bigint::_bigint_to<int>(block.GetLength().GetVlIntValue()));
        if(value<0){
            return false;
        }
        this->SetUriScheme(value);
        return true;
    }
}
