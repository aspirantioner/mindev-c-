#include "mindev/include/component/signaturefield.h"

namespace mindev::component{

    template<typename... Args>
    std::optional<SignatureInfo> BuildSignatureInfo(Args... args);

    template<typename T>
    std::optional<SignatureValue> BuildSignatureValue(T&& val);

    int SignatureField::WireEncode(mindev::encoding::Encoder& encoder){
        if(this->signatures.Length()==0){
            return 0;
        }
        int totalLength = 0;
        int tmpLen = 0;
        for(auto iter = this->signatures.GetSignatures().rbegin();iter!=this->signatures.GetSignatures().rend();iter++){
            tmpLen = iter->GetSigValue().WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
            tmpLen = iter->GetSigInfo().WireEncode(encoder);
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
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(mindev::encoding::TLV::TlvSignatureField));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool SignatureField::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvSignatureField))){
            return  false;
        }
        if(!block.ParseSubElements()){
            return false;
        }
        mindev::encoding::ElementContainer subElements = block.GetSubElements();
        if(subElements.Length()%2!=0){
            return false;
        }
        SignatureContainer container;
        for(int i = 0;i<subElements.Length();i+=2){
            auto val1 = BuildSignatureInfo(subElements.GetElements()[i]);
            if(!val1.has_value()){
                return false;
            }
            auto info = val1.value();
            
            auto val2 = BuildSignatureValue(subElements.GetElements()[i+1]);
            if(!val2.has_value()){
                return false;
            }
            auto value = val2.value();
            
            container.AddElement(Signature(info,value));
        }
        this->signatures.Clear();
        this->signatures = container;
        return true;
    }
}
