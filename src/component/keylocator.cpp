#include "mindev/include/component/keylocator.h"

namespace mindev::component{
    int KeyLocator::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        
        int tmpLen = this->identifier.WireEncode(encoder);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(mindev::encoding::TLV::TlvKeyLocator));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        return totalLength;
    }
    bool KeyLocator::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvKeyLocator))){
            return false;
        }
        if(!block.ParseSubElements()){
            return false;
        }
        if(block.GetSubElements().Length()!=1){
            return false;
        }
        auto val = block.GetSubElements().GetBlock(0);
        if(!val.has_value()){
            return false;
        }
        return this->identifier.WireDecode(val.value());
    }
}
