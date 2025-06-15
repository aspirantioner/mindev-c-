#include "mindev/include/component/readonlyfield.h"

namespace mindev::component{
    int ReadOnlyField::WireEncode(mindev::encoding::Encoder& encoder){
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

        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(mindev::encoding::TLV::TlvReadOnlyField));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    std::option<std::reference_wrapper<Block>> ReadOnlyField::GetBlockByType(const mindev::encoding::VlInt& tlvType){
        if(this->blocks.GetBlockByType(tlvType)){
            return this->blocks.GetBlockByType(tlvType);
        }else{
            return std::nullopt;
        }
    }
    bool ReadOnlyField::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(),mindev::encoding::VlInt(mindev::encoding::TLV::TlvReadOnlyField))){
            return false;
        }
        if(!block.ParseSubElements()){
            return false;
        }
        this->blocks = block.GetSubElements();
        return true;
    }
}
