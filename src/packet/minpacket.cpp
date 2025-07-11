#include "mindev/include/packet/minpacket.h"
#include "mindev/include/encoding/tlv.h"
#include "mindev/include/component/identifierwrapper.h"

namespace mindev::packet{
    std::optional<mindev::encoding::VlInt> MINPacket::GetPacketType(){
        auto identifierWrapper=this->identifierField.GetIdentifier(0);
        if(!identifierWrapper.has_value()){
            return std::nullopt;
        }
        return identifierWrapper.value().get().GetTlvType();
    }
    int MINPacket::WireEncode(mindev::encoding::Encoder& encoder){
        if(!this->IsPacketValid()){
            return -1;
        }
        int totalLength=0;
        //编码 TLV-VALUE
    
        //可变区
        int tmpLen =this->mutableField.WireEncode(encoder);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        
        //只读区
        tmpLen=this->readOnlyField.WireEncode(encoder);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        
        //签名区
        tmpLen=this->signatureField.WireEncode(encoder);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        
        //标识区
        tmpLen=this->identifierField.WireEncode(encoder);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        
        //编码包TLV-LENGTH
        mindev::encoding::VlInt vlInt(totalLength);
        tmpLen=encoder.PrependVarNumber(vlInt);
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        //编码包TLV-TYPE
        tmpLen=encoder.PrependVarNumber(this->packetType);
        if (tmpLen < 0)
        {
            return -1;
        }
        totalLength+=tmpLen;        
        return totalLength;
    }
    bool MINPacket::WireDecode(mindev::encoding::Block& block){
        //首先判断包是否有效
        if(!block.IsValid()){
            return false;
        }
        //首先解析子Block
        if(!block.ParseSubElements()){
            return false;
        }
        //解析包类型
        this->packetType=block.GetType();
        //标记 用来记录是否满足必要条件
        bool existIdentifier=false;
        for(auto elem:block.GetSubElements().GetElements()){
            auto type = bigint::_bigint_to<int>(elem.GetType().GetVlIntValue());
            switch(type){
                case mindev::encoding::TLV::TlvIdentifierField:
                    if(!elem.ParseSubElements()){
                        return false;
                    }
                    if(!elem.HasSubElement()){
                        return false;
                    }
                    if(!this->identifierField.WireDecode(elem)){
                        return false;
                    }
                    existIdentifier = true;
                    break;
                case mindev::encoding::TLV::TlvSignatureField:
                    if(!this->signatureField.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvReadOnlyField:
                    if(!this->readOnlyField.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvMutableField:
                    if(!this->mutableField.WireDecode(elem)){
                        return false;
                    }
                    break;
                default:
                    return false;
            }
        }
        if(!existIdentifier){
            return false;
        }
        return true;
    }
}
