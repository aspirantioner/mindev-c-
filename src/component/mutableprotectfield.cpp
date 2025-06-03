#include "mindev/include/component/mutableprotectfield.h"

namespace mindev::component{
    int MutableProtectField::WireEncode(mindev::encoding::Encoder& encoder){
        
        if(this->blocks.Length()==0){
            return 0;
        }

        int totalLength = 0;
        int tmpLen = 0;
        for(auto iter = this->blocks.GetElements().rbegin();iter!=this->blocks.GetElements().rend();iter++){
            tmpLen = encoder.PrependBlock(*iter);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }
        
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvMutableProtectField);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool MutableProtectField::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvMutableProtectField))){
            return false;
        }
        if(!block.ParseSubElements()){
            return false;
        }
        this->blocks = block.GetSubElements();
        return true;
    }
}
