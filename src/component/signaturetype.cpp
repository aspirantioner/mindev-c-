#include "mindev/include/component/signaturetype.h"

namespace mindev::component{
    int SignatureType::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        
        int tmpLen = encoder.PrependNonNegativeInteger(this->value.GetSignatureAlgorithm());
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(mindev::encoding::TLV::TlvSignatureType));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool SignatureType::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvSignatureType))){
            return false;
        }
        long value = mindev::encoding::TLV::ReadNonNegativeInteger(block.GetValue(), 0,bigint::_bigint_to<int>(block.GetLength().GetVlIntValue()));
        if(value<0){
            return false;
        }
        this->value = SignatureAlgorithm(value);
        return true;
    }
}
