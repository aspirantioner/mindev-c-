#include "mindev/include/component/controlparameterlogicfacepersistency.h"

namespace mindev::component{
    int ControlParameterLogicFacePersistency::WireEncode(mindev::encoding::Encoder& encoder){
        int totalLength = 0;
        int tmpLen = encoder.PrependNonNegativeInteger(this->persistency);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvManagementLogicFacePersistency);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool ControlParameterLogicFacePersistency::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementLogicFacePersistency))){
            return false;
        }
        auto value = mindev::encoding::TLV::ReadNonNegativeInteger(block.GetValue(), 0, bigint::_bigint_to<int>(block.GetLength().GetVlIntValue()));
        if(value<0){
            return false;
        }
        this->SetPersistency(value);
        return true;
    }
}
