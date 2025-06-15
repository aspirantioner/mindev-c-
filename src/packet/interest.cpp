#include "mindev/include/packet/interest.h"
#include "mindev/include/encoding/selfencodingbase.h"
#include "mindev/include/encoding/tlv.h"
#include "mindev/include/component/elementcontainer.h"
#include "mindev/include/component/identifierwrapper.h"
#include <optional>


namespace mindev::packet{
    Interest::Interest(const mindev::component::Identifier& name,const mindev::component::Payload& payload,const mindev::component::InterestLifeTime& interestLifeTime,const mindev::component::CanBePrefix& canBePrefix,const mindev::component::MustBeRefresh& mustBeRefresh,const mindev::component::Nonce& nonce,const mindev::component::HopLimit& hopLimit,const mindev::component::NackHeader& nackHeader,const mindev::component::CongestionMark& congestionMark,const mindev::component::TTL& ttl,const mindev::component::IncomingLogficFaceId& incomingLogficFaceId){
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
        if(minPacket.packetType == mindev::encoding::VlInt(mindev::encoding::TLV::TlvPacketMINManagement)){
            interest->isCommandInterest=true;
        }
        interest->minPacket.signatureField.SetSignatures(minPacket.signatureField.GetSignatures());
        if(!interest->DoExtraDataFromMINPacket(minPacket)){
            return std::nullopt;
        }
        return interest;
    }


void Interest::SetNameByString(const std::string& name){
    mindev::component::Identifier identifier(name);
    this->name=identifier;
}

bool Interest::MatchesName(const mindev::component::Identifier& identifier){
    return this->name==identifier;
}

bool Interest::MatchesData(const Data& data){
    throw std::logic_error("implement me!");
}

bool Interest::MatchesInterest(Interest& interest){
    throw std::logic_error("implement me!");
}


bool Interest::DoFillDataToFields(MINPacket& minPacket){
    //填充可变区
    minPacket.mutableField.mutableProtectField.ClearBlocks();
    //congestionMark
    auto block =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->congestionMark);
    if(block==std::nullopt){
        return false;
    }
    minPacket.mutableField.mutableProtectField.AddBlock(*block);

    //填充可变非受保护区
    minPacket.mutableField.mutableDangerousField.ClearBlocks();
    //ttl
    auto block2 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->ttl);
    if(block2=std::nullopt){
        return false;
    }
    minPacket.mutableField.mutableDangerousField.AddBlock(*block2);
    //incomingLogicFaceId
    if(this->incomingLogficFaceId.IsInitial()){
        auto block3 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->incomingLogficFaceId);
        if(block3==std::nullopt){
            return false;
        }
        minPacket.mutableField.mutableDangerousField.AddBlock(*block3);
    }
    //填充只读区
    minPacket.readonlyField.ClearBlocks();
    //canBePrefix
    if(this->canBePrefix.GetCanBePrefix()){
        auto block4 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->canBePrefix);
        if(block4==std::nullopt){
            return false;
        }
        minPacket.readonlyField.AddBlock(*block4);
    }
    //mustBeRefresh
    if(this->mustBeRefresh.GetMustBeRefresh()){
        auto block5 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->mustBeRefresh);
        if(block5==std::nullopt){
            return false;
        }
        minPacket.readonlyField.AddBlock(*block5);
    }
    //interestLifeTime
    if(!this->interestLifeTime.IsInitial()){
        //默认生存期是4s
        this->interestLifeTime.SetInterestLifeTime(4000);
    }
    auto block6 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->interestLifeTime);
    if(block6==std::nullopt){
        return false;
    }
    minPacket.readonlyField.AddBlock(*block6);
    //nonce
    if(!this->nonce.IsInitial()){
        //如果没有指定随机数，随机生成一个随机数
        this->nonce.RefreshNonce();
    }
    auto block7 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->nonce);
    if(block7==std::nullopt){
        return false;
    }
    minPacket.readonlyField.AddBlock(*block7);
    //hopLimit
    if(this->hopLimit.IsInitial()){
        auto block8 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->hopLimit);
        if(block8==std::nullopt){
            return false;
        }
        minPacket.readonlyField.AddBlock(*block8);
    }
    //nackHeader
    if(this->nackHeader.IsInitial()){
        auto block9 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->nackHeader);
        if(block9==std::nullopt){  
            return false;
    }
        minPacket.readonlyField.AddBlock(*block9);
    }
    //payload
    auto block10 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->payload);
    if(block10==std::nullopt){
        return false;
    }
    minPacket.readOnyField.AddBlock(*block10);
    //填充标识区
    minPacket.identifierField.ClearBlocks();
    auto identifierWrapper=mindev::component::IdentifierWrapper().CreateContentInterestIdentifierByComponent(this->name.GetComponents());
    if(identifierWrapper==std::nullopt){
        return false;
    }
    minPacket.identifierField.AddIdentifier(*identifierWrapper);
    return true;
}
bool Interest::FillDataToFields(){
    return this->DoFillDataToMINPacket(this->minPacket);
}

bool Interest::DoExtraDataFromFields(const MINPacket& minPacket){
    //解析可变区
    auto block=minPacket.mutableField.mutableProtectField.GetFirstBlockByType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvCongestionMark));
    if(block){
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
    for(auto elem:minpacket.readonlyField.GetBlocks().GetElements()){
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
    auto identifierWrapper=minPacket.identifierField.GetIdentifierByType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifierContentInterest));
    if(identifierWrapper==std::nullopt){
        return false;
    }
    this->SetName(interestIdentifierWrapper->GetIdentifier());
    return true;
    }

    bool Interest::ExtraDataFromMINPacket(){
        return this->DoExtraDataFromMINPacket(this->minPacket);
    }

    int Interest::WireEncode(mindev::encoding::Encoder& encoder){
        //首先将各属性填充到分区当中
        if(!this->FillDataToMINPacket()){
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
    if(this->minPacket.packetType.IsEqual(mindev::encoding::TLV::TlvPacketMINManagement)){
        this->isCommandInterest=true;
    }
}
}

