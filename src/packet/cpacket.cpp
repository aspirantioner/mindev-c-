#include "mindev/include/packet/cpacket.h"
#include "mindev/include/encoding/vlint.h"
#include "mindev/include/encoding/sizet.h"
#include "mindev/include/encoding/selfencodingbase.h"
#include "mindev/include/encoding/vlint.h"

namespace mindev::packet{
CPacket::CPacket(const mindev::component::Identifier& srcIdentifier,const mindev::component::Identifier& dstIdentifier,const mindev::component::Payload& payload,const mindev::component::TTL& ttl) {
    this->srcIdentifier = srcIdentifier;
    this->dstIdentifier = dstIdentifier;
    this->payload = payload;
    this->ttl = ttl;
};
/**
 * @Description: 编码CPacket 
 */
bool CPacket::EncodeSelf() {
    mindev::encoding::Encoder encoder;
    if(!encoder.EncoderReset(mindev::encoding::SizeT(mindev::encoding::Encoder::MaxPacketSize),mindev::encoding::SizeT(0))){
                return false;
    }
    int buflen=this->WireEncode(encoder);
    if(buflen<=0){
        return false;
    }
    this->rawData=encoder.GetBuffer();
    return true;
}

std::optional<CPacket> CPacket::CreateCPacketByMINPacket(const MINPacket& minpacket) {
    CPacket cPacket;
    cPacket.minPacket.signatureField.SetSignatures(this->minPacket.signatureField.GetSignatures());
    if(!cPacket.DoExtraDataFromFields(minPacket)){
        return std::nullopt;
    }
    return cPacket;
}

bool CPacket::DoFillDataToFields(MINPacket& minPacket) {
    // 可变区 => 受保护区（无）

    // 填充可变区 => 非受保护区
    // 首先清除所有的Block
    minPacket.mutableField.mutableDangerousField.ClearBlocks();
    auto block = mindev::encoding::SelfEncodingBase().SelfWireEncode(this->ttl);
    if (block == std::nullopt) {
        return false;
    }
    minPacket.mutableField.mutableDangerousField.AddBlock(block.value());
    // 填充只读区
    // 首先清除所有的Block
    if (!((this->payload).GetValue().empty())){
        minPacket.readOnlyField.ClearBlocks();
        auto block = mindev::encoding::SelfEncodingBase().SelfWireEncode(this->payload);
        if (block == std::nullopt) {    
            return false;
        }
        minPacket.readOnlyField.AddBlock(*block);
    }
    //填充标识区
    // 首先清除所有的标识
    minPacket.identifierField.ClearIdentifiers();
    mindev::component::IdentifierWrapper srcIdentifierWrapper(mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifierCommon), this->srcIdentifier);
    mindev::component::IdentifierWrapper dstIdentifierWrapper(mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifierCommon), this->dstIdentifier);
    minPacket.identifierField.AddIdentifier(srcIdentifierWrapper);
    minPacket.identifierField.AddIdentifier(dstIdentifierWrapper);
    return true;
};
bool CPacket::FillDataToFields(){
    return DoFillDataToFields(this->minPacket);
}

bool CPacket::DoExtraDataFromFields(const MINPacket& minPacket) {
    // 提取 Payload
    auto payloadBlock = const_cast<MINPacket&>(minPacket).readOnlyField.GetBlockByType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvPayload));
    if(!payloadBlock.has_value()){
        return false;
    }
    if (!this->payload.WireDecode(payloadBlock.value().get())) {
        return false;
    };
    
    // 提取 TTL
    auto ttlBlock = const_cast<MINPacket&>(minPacket).mutableField.mutableDangerousField.GetFirstBlockByType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvTTL));
    if(!ttlBlock.has_value()){
        return false;
    }
    if (!this->ttl.WireDecode(ttlBlock.value().get())) {
        return false;
    };

    // 提取标识
    auto srcIdentifierWrapper = const_cast<MINPacket&>(minPacket).identifierField.GetIdentifier(0);
    if(!srcIdentifierWrapper.has_value()){
        return false;
    }
    auto dstIdentifierWrapper = const_cast<MINPacket&>(minPacket).identifierField.GetIdentifier(1);
    if(!dstIdentifierWrapper.has_value()){
        return false;
    }
    this->srcIdentifier=srcIdentifierWrapper.value().get().GetIdentifier();
    this->dstIdentifier=dstIdentifierWrapper.value().get().GetIdentifier();
    return true;
};
bool CPacket::ExtraDataFromFields(){
    return DoExtraDataFromFields(this->minPacket);
}
int CPacket::WireEncode(mindev::encoding::Encoder& encoder) {
    //首先将属性填充到分区当中
    if(!this->FillDataToFields()){
        return -1;
    }
    //指定包类型
    this->minPacket.packetType=mindev::encoding::VlInt(mindev::encoding::TLV::TlvPacketMINCommon);
    return this->minPacket.WireEncode(encoder);
}
bool CPacket::WireDecode(mindev::encoding::Block& block) {
    if(!this->minPacket.WireDecode(block)){
        return false;
    }
    return this->ExtraDataFromFields();
}
}
