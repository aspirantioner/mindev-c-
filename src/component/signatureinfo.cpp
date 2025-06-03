#include "mindev/include/component/signatureinfo.h"

namespace mindev::component{
    int SignatureInfo::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        int tmpLen = 0;
        
        if(this->keyLocator.IsValid()){
            tmpLen = this->keyLocator.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }
        
        tmpLen = this->signatureType.WireEncode(encoder);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(mindev::encoding::TLV::TlvSignatureInfo));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool SignatureInfo::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvSignatureInfo))){
            return  false;
        }
        if(!block.ParseSubElements()){
            return false;
        }
        bool findSignatureType = false;
        int elementsize = block.GetSubElements().Length();
        for(auto elem:block.GetSubElements().GetElements()){
            int type = bigint::_bigint_to<int>(elem.GetType().GetVlIntValue());
            switch (type) { 
                case mindev::encoding::TLV::TlvSignatureType:
                    if(!this->signatureType.WireDecode(elem)){
                        return false;
                    }
                    findSignatureType = true;
                    break;
                case mindev::encoding::TLV::TlvKeyLocator:
                    if(!this->keyLocator.WireDecode(elem)){
                        return false;
                    }
                    break;
                default:
                    return false;
            }
        }
        return findSignatureType;
    }
}
