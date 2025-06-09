#include "mindev/include/component/controlparameterprefix.h"

namespace mindev::component{
    int ControlParameterPrefix::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        int tmpLen = this->prefix.WireEncode(encoder);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvManagementPrefix);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool ControlParameterPrefix::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementPrefix))){
            return false;
        };
        if(!block.ParseSubElements()){
            return false;
        }
        Identifier identifier;
        auto val = block.GetElement(mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifier));
        if(!val.has_value()){
            return false;
        }
        if(!identifier.WireDecode(val.value())){
            return false;
        };
        this->SetPrefix(identifier);
        return true;
    }
}
