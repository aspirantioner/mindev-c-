#include "mindev/include/packet/lppacket.h"
#include <vector>
#include "mindev/include/packet/minpacket.h"
#include "mindev/include/encoding/vlint"
#include "mindev/include/encoding/tlv"
namespace mindev::packet {

std::vector<char> LpPacket::GetRawPayload() const {
    return this->rawPayload;
}

bool LpPacket::DecodeSelf(){
    std::vector<char> payload=this->payload.GetValue();
    mindev::component::Block block(payload,true);
    MINPacket minPacket;
    if(!minPacket.WireDecode(block)){
        return false;
    }
    CPacket cPacket=CPacket().CreateCPacketbyMINPacket(minPacket);
    this->rawPayload=cpacket.GetValue();
    return true;
}

LpPacket::LpPacket(){}

LaPacket::LaPacket(indev::component::LpPacketHeader& lpPacketHeader, mindev::component::Payload& payload){
    this.lpPacketHeader=lpPacketHeader;
    this.payload=payload;
}

void LpPacket::SetId(long fragmentId){
    mindev::component::LpPacketFragmentId lpPacketFragmentId(fragmentId);
    this.lpPacketHeader.SetLpPacketFragmentId(lpPacketFragmentId);
}

void LpPacket::GetId(){
    return this->lpPacketHeader.GetLpPacketFragmentId().GetId();
} 
void LpPacket::SetFragmentNum(long fragmentNum){
    mindev::component::LpPacketFragmentNum lpPacketFragmentNum(fragmentNum);
    this->lpPacketHeader.SetLpPacketFragmentNum(lpPacketFragmentNum);
}

long LpPacket::GetFragmentNum(){
    return this->lpPacketHeader.GetLpPacketFragmentNum().GetFragmentNum();
}

void LpPacket::SetFragmentSeq(long fragmentSeq){
    mindev::component::LpPacketFragmentSeq lpPacketFragmentSeq(fragmentSeq);
    this->lpPacketHeader.SetLpPacketFragmentSeq(lpPacketFragmentSeq);
}
long LpPacket::GetFragmentSeq(){
    return this->lpPacketHeader.GetLpPacketFragmentSeq().GetFragmentSeq();
}

void LpPacket::SetValue(std::vector<char>& value){
    this->payload.SetValue(value);
}

std::vector<char>& LpPacket::GetValue() const{
    return this->payload.GetValue();
}

/**
     * 将 LpPacket 线速编码为一个 TLV
     *
     * @param encoder
     * @return
     * @throws ComponentException
     * @throws PacketException
     */
int LpPacket::WireEncode(mindev::encoding::Encoder& encoder){
    int totalLength=0;
    //编码 TLV-VALUE
    //LpHeader
    int tmpLen=this->lpPacketHeader.WireEncode(encoder);
    if(tmpLen<0){
        return -1;
    }
    totalLength+=tmpLen;
    //Fragment
    tmpLen=this->payload.WireEncode(encoder);
    if(tmpLen<0){
        return -1;
    }
    totalLength+=tmpLen;
    //编码TLV-LENGTH
    mindev::encoding::VlInt vlInt(totalLength);
    tmpLen=encoder.PrependVarNumber(vlInt);
    if(tmpLen<0){
        return -1;
    }
    totalLength+=tmpLen;
    //编码TLV-TYPE
    mindev::encoding::VlInt vlInt2(mindev::encoding::TLV.TlvLpPacket);
    tmpLen=encoder.PrependVarNumber(vlInt2);
    if(tmpLen<0){
        return -1;
    }
    totalLength+=tmpLen;
    return totalLength;
}
bool LpPacket::WireDecode(mindev::encoding::Block& block){
    //检查Type是否正确
    mindev::encoding::VlInt vlInt1(mindev::encoding::TLV.TlvLpPacket);
    if(!mindev::encoding::TLV.ExpectType(block.GetType(),vlInt1)){
        return false;
    }
    //解析子组件
    if(!block.ParseSubElements()){
        return false;
    }
    mindev::encoding::ElementContainer& elementContainer=block.GetSubElements();
    for(int i=0;i<elementContainer.Length();i++){
        mindev::encoding::Block newBlock=elementContainer.GetBlock(i);
        int type=newBlock.GetType().GetVlIntValue2Int();
        switch(type){
            case mindev::encoding::TLV.TlvLpPacketHeader:
                if(!this->lpPacketHeader.WireDecode(newBlock)){
                    return false;
                }
                break;
            case mindev::encoding::TLV.TlvPayload:
                if(!this->payload.WireDecode(newBlock)){
                    return false;
                }
                break;
        }
    }
    return true;
}
}



 