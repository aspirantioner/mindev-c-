#include "mindev/include/component/identifierfield.h"

namespace mindev::component{
    int IdentifierField::WireEncode(mindev::encoding::Encoder& encoder){
        if(this->identifiers.Length()<=0){
            return -1;
        }

        int totalLength = 0;
        int tmpLen = 0;

        for(auto iter = this->identifiers.GetIdentifierWrappers().rbegin();iter!=this->identifiers.GetIdentifierWrappers().rend();iter++){
            tmpLen = iter->WireEncode(encoder);
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

        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvIdentifierField);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        return totalLength;
    }
    bool IdentifierField::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::TLV::TlvIdentifierField)){
            return false;
        }
        if(!block.ParseSubElements()){
            return false;
        }
        IdentifierContainer identifiercontainer;
        for(auto iter = block.GetSubElements().GetElements().begin();iter!=block.GetSubElements().GetElements().end();iter++){
            IdentifierWrapper identifierwrapper(iter);
            if(!identifierwrapper.IsValid()){
                return false;
            }
            identifiercontainer.AddElement(identifierwrapper);
        }
        this->identifiers = identifiercontainer;
        return true;
    }
}
