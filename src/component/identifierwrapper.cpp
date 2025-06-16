#include "mindev/include/component/identifierwrapper.h"

namespace mindev::component{
    int IdentifierWrapper::WireEncode(mindev::encoding::Encoder& encoder){
        
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
    
        tmpLen = encoder.PrependVarNumber(this->tlvType);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool IdentifierWrapper::WireDecode(mindev::encoding::Block& block){
        if(mindev::encoding::TLV::IsValidIdentifierType(block.GetType())){
            return false;
        }
        if(!block.ParseSubElements()){
            return false;
        }
        if(block.GetSubElements().Length()!=1){
            return false;
        }
        auto val = Identifier::BuildIdentifierByBlock(block);
        if(!val.has_value()){
            return false;
        }
        this->identifier = val.value();
        this->tlvType = block.GetType();
        return true;
    }
}
