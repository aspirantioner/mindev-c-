#include "mindev/include/component/mutabledangerousfield.h"

namespace mindev::component{
    int MutableDangerousField::WireEncode(mindev::encoding::Encoder& encoder){
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

        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvMutableDangerousField);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool MutableDangerousField::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvMutableDangerousField))){
            return false;
        }
        if(!block.ParseSubElements()){
            return false;
        }
        this->blocks = block.GetSubElements();
        return true;
    }
}
