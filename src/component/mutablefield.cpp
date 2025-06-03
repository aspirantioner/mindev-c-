#include "mindev/include/component/mutablefield.h"

namespace mindev::component{
    int MutableField::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;

        int tmpLen = this->mutableDangerousFiled.WireEncode(encoder);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;

        tmpLen = this->mutableProtectField.WireEncode(encoder);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvMutableField);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        return totalLength;
    }
    bool MutableField::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvMutableField))){
            return false;
        }
        if(!block.ParseSubElements()){
            return false;
        }
        for(auto subblock:block.GetSubElements().GetElements()){
            if(subblock.GetType() == mindev::encoding::VlInt(mindev::encoding::TLV::TlvMutableProtectField)){
                if(!this->mutableProtectField.WireDecode(subblock)){
                    return false;
                }
            }else if(subblock.GetType() == mindev::encoding::VlInt(mindev::encoding::TLV::TlvMutableDangerousField)){
                if(!this->mutableDangerousFiled.WireDecode(subblock)){
                    return false;
                }
            }else{
                return false;
            }
        }
        return true;
    }
}
