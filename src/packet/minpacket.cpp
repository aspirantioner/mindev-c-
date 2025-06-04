#include "mindev/include/packet/minpacket.h"
#include "mindev/include/encoding/tlv.h"
#include "mindev/include/component/identifierwrapper.h"

namespace mindev::packet{
    public:
    bool MINPacket::IsPacketValid(){
        return mindev::encoding::TLV.IsValidPacketType(this->packetType);
    }
    mindev::encoding::VlInt MINPacket::GetPacketType(){
        mindev::encoding::IdentifierWrapper identifierWrapper=this->identifierField.GetIdentifier(0);
        return identifierWrapper.GetTlvType();
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
        tmplen=encoder.PrependVarNumber(this->packetType);
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
        //解析四个标识区
        int elementSize=block.GetSubElements().Length();
        for(int i=0;i<elementSize;i++){
            mindev::encoding::Block cacheBlock=block.getSubElements().GetBlock(i);
            int judgeType=cacheBlock.GetType().GetVlIntValue2Int();
            switch(judgeType){
                case mindev::encoding::TLV.TlvIdentifierField://目的标识区
                    //解析标识区 保证其中至少存在一个标识
                    if(!cacheBlock.ParseSubElements()){
                        return false;
                    }
                    if(!cacheBlock.HasSubElements()){
                        return false;
                    }
                    //解析标识区
                    if(!this->identifierField.WireDecode(cacheBlock)){
                        return false;
                    }
                    //标识解析到了至少一个以上的合法标识
                    existIdentifier=true;
                    break;
                case mindev::encoding::TLV.TlvSignatureField://签名区
                    //解析签名区,保证如果存在签名，则签名均符合格式
                    if(!this->signatureField.WireDecode(cacheBlock)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV.TlvReadOnlyField://只读区
                    //解析只读区
                    if(!this->readOnlyField.WireDecode(cacheBlock)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV.TlvMutableField://可变区
                    //解析可变区
                    if(!this->mutableField.WireDecode(cacheBlock)){
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
