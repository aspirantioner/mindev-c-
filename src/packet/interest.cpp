#include "mindev/include/packet/interest.h"
#include "mindev/include/encoding/selfencodingbase.h"
#include "mindev/include/encoding/tlv.h"
#include "mindev/include/encoding/elementcontainer.h"
#include "mindev/include/component/identifierwrapper.h"
#include <optional>

namespace mindev::component{
    template<typename T>
    IdentifierWrapper BuildIdentifierWrapper(T&& val,decltype(mindev::encoding::TLV::TlvInvalid) flag);
};

namespace mindev::packet{
    Interest::Interest(const mindev::component::Identifier& name,const mindev::component::Payload& payload,const mindev::component::InterestLifeTime& interestLifeTime,const mindev::component::CanBePrefix& canBePrefix,const mindev::component::MustBeRefresh& mustBeRefresh,const mindev::component::Nonce& nonce,const mindev::component::HopLimit& hopLimit,const mindev::component::NackHeader& nackHeader,const mindev::component::CongestionMark& congestionMark,const mindev::component::TTL& ttl,const mindev::component::IncomingLogicFaceId& incomingLogficFaceId){
        this->name=name;
        this->payload=payload;
        this->interestLifeTime=interestLifeTime;
        this->canBePrefix=canBePrefix;
        this->mustBeRefresh=mustBeRefresh;
        this->nonce=nonce;
        this->hopLimit=hopLimit;
        this->nackHeader=nackHeader;
        this->congestionMark=congestionMark;
        this->ttl=ttl;
        this->incomingLogficFaceId=incomingLogficFaceId;
    }

    std::optional<Interest> Interest::CreateInterestByMINPacket(const MINPacket& minPacket){
        Interest interest;
        if(const_cast<MINPacket&>(minPacket).packetType == mindev::encoding::VlInt(mindev::encoding::TLV::TlvPacketMINManagement)){
            interest.isCommandInterest=true;
        }
        interest.minPacket.signatureField.SetSignatures(const_cast<MINPacket&>(minPacket).signatureField.GetSignatures());
        if(!interest.DoExtraDataFromFields(const_cast<MINPacket&>(minPacket))){
            return std::nullopt;
        }
        return interest;
    }

bool Interest::DoFillDataToFields(MINPacket& minPacket){
    //填充可变区
    minPacket.mutableField.mutableProtectField.ClearBlocks();
    //congestionMark
    auto block = mindev::encoding::SelfEncodingBase().SelfWireEncode(this->congestionMark);
    if(block==std::nullopt){
        return false;
    }
    minPacket.mutableField.mutableProtectField.AddBlock(*block);

    //填充可变非受保护区
    minPacket.mutableField.mutableDangerousField.ClearBlocks();
    //ttl
    auto block2 = mindev::encoding::SelfEncodingBase().SelfWireEncode(this->ttl);
    if(block2==std::nullopt){
        return false;
    }
    minPacket.mutableField.mutableDangerousField.AddBlock(*block2);
    //incomingLogicFaceId
    if(this->incomingLogficFaceId.isInitial()){
        auto block3 = mindev::encoding::SelfEncodingBase().SelfWireEncode(this->incomingLogficFaceId);
        if(block3==std::nullopt){
            return false;
        }
        minPacket.mutableField.mutableDangerousField.AddBlock(*block3);
    }
    //填充只读区
    minPacket.readOnlyField.ClearBlocks();
    //canBePrefix
    if(this->canBePrefix.GetCanBePrefix()){
        auto block4 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->canBePrefix);
        if(block4==std::nullopt){
            return false;
        }
        minPacket.readOnlyField.AddBlock(*block4);
    }
    //mustBeRefresh
    if(this->mustBeRefresh.GetMustBeRefresh()){
        auto block5 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->mustBeRefresh);
        if(block5==std::nullopt){
            return false;
        }
        minPacket.readOnlyField.AddBlock(*block5);
    }
    //interestLifeTime
    if(!this->interestLifeTime.isInitial()){
        //默认生存期是4s
        this->interestLifeTime.SetInterestLifeTime(4000);
    }
    auto block6 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->interestLifeTime);
    if(block6==std::nullopt){
        return false;
    }
    minPacket.readOnlyField.AddBlock(*block6);
    //nonce
    if(!this->nonce.isInitial()){
        //如果没有指定随机数，随机生成一个随机数
        this->nonce.RefreshNonce();
    }
    auto block7 = mindev::encoding::SelfEncodingBase().SelfWireEncode(this->nonce);
    if(block7==std::nullopt){
        return false;
    }
    minPacket.readOnlyField.AddBlock(*block7);
    //hopLimit
    if(this->hopLimit.isInitial()){
        auto block8 = mindev::encoding::SelfEncodingBase().SelfWireEncode(this->hopLimit);
        if(block8==std::nullopt){
            return false;
        }
        minPacket.readOnlyField.AddBlock(*block8);
    }
    //nackHeader
    if(this->nackHeader.isInitial()){
        auto block9 = mindev::encoding::SelfEncodingBase().SelfWireEncode(this->nackHeader);
        if(block9==std::nullopt){  
            return false;
        }
        minPacket.readOnlyField.AddBlock(*block9);
    }
    //payload
    auto block10 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->payload);
    if(block10==std::nullopt){
        return false;
    }
    minPacket.readOnlyField.AddBlock(*block10);
    //填充标识区
    minPacket.identifierField.ClearIdentifiers();
    auto identifierWrapper= mindev::component::BuildIdentifierWrapper(this->name.GetComponents(),mindev::encoding::TLV::TlvIdentifierContentInterest);
    if(!identifierWrapper.IsValid()){
        return false;
    }
    minPacket.identifierField.AddIdentifier(identifierWrapper);
    return true;
}
bool Interest::FillDataToFields(){
    return this->DoFillDataToFields(this->minPacket);
}

bool Interest::DoExtraDataFromFields(MINPacket& minPacket){
    //解析可变区
    auto block=minPacket.mutableField.mutableProtectField.GetFirstBlockByType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvCongestionMark));
    if(block.has_value()){
        if(!this->congestionMark.WireDecode(*block)){
            return false;
        }
    }
    
    block =minPacket.mutableField.mutableDangerousField.GetFirstBlockByType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvTTL));
    if(block){
        if(!this->ttl.WireDecode(*block)){
            return false;
        }
    }
    
    block =minPacket.mutableField.mutableDangerousField.GetFirstBlockByType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvIncomingLogicFaceId));
    if(block){
        if(!this->incomingLogficFaceId.WireDecode(*block)){
            return false;
        }
    }
    
    //解析只读区
    for(auto elem:minPacket.readOnlyField.GetBlocks().GetElements()){
        auto type = bigint::_bigint_to<int>(elem.GetType().GetVlIntValue());
        switch(type){
            case mindev::encoding::TLV::TlvCanBePrefix:
                if(!this->canBePrefix.WireDecode(elem)){
                    return false;
                }
                break;
            case mindev::encoding::TLV::TlvMustBeRefresh:
                if(!this->mustBeRefresh.WireDecode(elem)){
                    return false;
                }
                break;
            case mindev::encoding::TLV::TlvInterestLifeTime:
                if(!this->interestLifeTime.WireDecode(elem)){
                    return false;
                }
                break;
            case mindev::encoding::TLV::TlvNonce:
                if(!this->nonce.WireDecode(elem)){
                    return false;
                }
                break;
            case mindev::encoding::TLV::TlvHopLimit:
                if(!this->hopLimit.WireDecode(elem)){
                    return false;
                }
                break;
            case mindev::encoding::TLV::TlvNackHeader:
                if(!this->nackHeader.WireDecode(elem)){
                    return false;
                }
                break;
            case mindev::encoding::TLV::TlvPayload:
                if(!this->payload.WireDecode(elem)){
                    return false;
                }
                break;
            default:
                break;
        }
    }
    //解析标识区
    auto interestIdentifierWrapper=minPacket.identifierField.GetIdentifierByType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifierContentInterest));
    if(interestIdentifierWrapper==std::nullopt){
        return false;
    }
    this->SetName(interestIdentifierWrapper.value().get().GetIdentifier());
    return true;
    }

    bool Interest::ExtraDataFromFields(){
        return this->DoFillDataToFields(this->minPacket);
    }

    int Interest::WireEncode(mindev::encoding::Encoder& encoder){
        //首先将各属性填充到分区当中
        if(!this->FillDataToFields()){
            return -1;
        }
        //指定包类型
        if(this->isCommandInterest){
            this->minPacket.packetType=mindev::encoding::VlInt(mindev::encoding::TLV::TlvPacketMINManagement);
        }
        else{
            this->minPacket.packetType=mindev::encoding::VlInt(mindev::encoding::TLV::TlvPacketMINCommon);
        }
        return this->minPacket.WireEncode(encoder);
}

bool Interest::WireDecode(mindev::encoding::Block& block){
    if(!this->minPacket.WireDecode(block)){
        return false;
    }
    if(this->minPacket.packetType == mindev::encoding::VlInt(mindev::encoding::TLV::TlvPacketMINManagement)){
        this->isCommandInterest=true;
    }
    return this->ExtraDataFromFields();
}
}

