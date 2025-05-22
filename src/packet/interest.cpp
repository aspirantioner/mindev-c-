#include "mindev/include/packet/interest.h"
#include "mindev/include/encoding/selfencodingbase.h"
#include "mindev/include/encoding/TLV.h"
#include "mindev/include/component/elementcontainer.h"
#include "mindev/include/component/identifierwrapper.h"



namespace mindev::packet{
Interest::Interest():minPacket(MINPacket()),canBePrefix(mindev::component::CanBePrefix()),mustBeReFresh(mindev::component::MustBeRefresh()),interestLifeTime(mindev::component::InterestLifeTime()),nonce(mindev::component::Nonce()),hopLimit(mindev::component::HopLimit()),payload(mindev::component::Payload()),congestionMark(mindev::component::CongestionMark()),ttl(mindev::component::TTL()),nackHeader(mindev::component::NackHeader()),incomingLogicFaceId(mindev::component::IncomingLogicFaceId()),identifier(mindev::component::Identifier()){};

Interest::Interest(Identifier& name,mindev::component::Payload& payload,mindev::component::InterestLifeTime& interestLifeTime,mindev::component::CanBePrefix& canBePrefix,mindev::component::MustBeRefresh& mustBeRefresh,mindev::component::Nonce& nonce,mindev::component::HopLimit& hopLimit,mindev::component::NackHeader& nackHeader,mindev::component::CongestionMark& congestionMark,mindev::component::TTL& ttl,mindev::component::IncomingLogficFaceId& incomingLogficFaceId){
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

std::unique_ptr<Interest> Interest::CreateInterestByMINPacket(MINPacket& minPacket){
    std::unique_ptr<Interest> interest(new Interest());
    if(minPacket.packetType.IsEqual(mindev::encoding::TLV.TlvPacketMINManagement)){
        interest->isCommandInterest=true;
    }
    interest->minPacket.signatureField.SetSignatures(minPacket.signatureField.GetSignatures());
    if(!interest->DoExtraDataFromMINPacket(minPacket)){
        return nullptr;
    }
    return interest;
}

mindev::component::Identifier& Interest::GetName(){
    return this->name;
}

void Interest::SetName(mindev::component::Identifier& name){
    this->name=name;
}

void Interest::SetNameByString(std::string& name){
    mindev::component::Identifier identifier(Identifier(name));
    this->name=identifier;
}

bool Interest::MatchesName(mindev::component::Identifier& identifier){
    return this->name==identifier;
}

bool Interest::MatchesData(Data& data){
    throw std::logic_error("implement me!");
}

bool Interest::MatchesInterest(Interest& interest){
    throw std::logic_error("implement me!");
}

std::string Interest::ToUri(){
    return this->name.ToUri();
}

bool Interest::AppendCommandParameters(mindev::mgmt::ControlParameters& parameters){
    return this->name.AppendCommandParameters(parameters);
}

bool Interest::AppendVersionNumber(long versionNumber){
    return this->name.AppendVersionNumber(versionNumber);
}

bool Interest::AppendFragmentNumber(long fragmentNumber){
    return this->name.AppendFragmentNumber(fragmentNumber);
}

bool Interest::DoFillDataToMINPacket(MINPacket& minPacket){
    //填充可变区
    minPacket.mutableField.mutableProtectField.ClearBlocks();
    //congestionMark
    std::unique_ptr<mindev::encoding::Block> block =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->congestionMark);
    if(block==nullptr){
        return false;
    }
    minPacket.mutableField.mutableProtectField.AddBlock(*block);

    //填充可变非受保护区
    minPacket.mutableField.mutableDangerousField.ClearBlocks();
    //ttl
    std::unique_ptr<mindev::encoding::Block> block2 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->ttl);
    if(block2==nullptr){
        return false;
    }
    minPacket.mutableField.mutableDangerousField.AddBlock(*block2);
    //incomingLogicFaceId
    if(this->incomingLogficFaceId.IsInitial()){
        std::unique_ptr<mindev::encoding::Block> block3 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->incomingLogficFaceId);
        if(block3==nullptr){
            return false;
        }
        minPacket.mutableField.mutableDangerousField.AddBlock(*block3);
    }
    //填充只读区
    minPacket.readonlyField.ClearBlocks();
    //canBePrefix
    if(this->canBePrefix.GetCanBePrefix()){
        std::unique_ptr<mindev::encoding::Block> block4 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->canBePrefix);
        if(block4==nullptr){
            return false;
        }
        minPacket.readonlyField.AddBlock(*block4);
    }
    //mustBeRefresh
    if(this->mustBeRefresh.GetMustBeRefresh()){
        std::unique_ptr<mindev::encoding::Block> block5 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->mustBeRefresh);
        if(block5==nullptr){
            return false;
        }
        minPacket.readonlyField.AddBlock(*block5);
    }
    //interestLifeTime
    if(!this->interestLifeTime.IsInitial()){
        //默认生存期是4s
        this->interestLifeTime.SetInterestLifeTime(4000);
    }
    std::unique_ptr<mindev::encoding::Block> block6 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->interestLifeTime);
    if(block6==nullptr){
        return false;
    }
    minPacket.readonlyField.AddBlock(*block6);
    //nonce
    if(!this->nonce.IsInitial()){
        //如果没有指定随机数，随机生成一个随机数
        this->nonce.RefreshNonce();
    }
    std::unique_ptr<mindev::encoding::Block> block7 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->nonce);
    if(block7==nullptr){
        return false;
    }
    minPacket.readonlyField.AddBlock(*block7);
    //hopLimit
    if(this->hopLimit.IsInitial()){
        std::unique_ptr<mindev::encoding::Block> block8 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->hopLimit);
        if(block8==nullptr){
            return false;
        }
        minPacket.readonlyField.AddBlock(*block8);
    }
    //nackHeader
    if(this->nackHeader.IsInitial()){
        std::unique_ptr<mindev::encoding::Block> block9 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->nackHeader);
        if(block9==nullptr){  
            return false;
    }
        minPacket.readonlyField.AddBlock(*block9);
    }
    //payload
    std::unique_ptr<mindev::encoding::Block> block10 =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->payload);
    if(block10==nullptr){
        return false;
    }
    minPacket.readOnyField.AddBlock(*block10);
    //填充标识区
    minPacket.identifierField.ClearBlocks();
    std::unique_ptr<mindev::component::IdentifierWrapper> identifierWrapper=mindev::component::IdentifierWrapper::IdentifierWrapper().CreateContentInterestIdentifierByComponent(this->name.GetComponents());
    if(identifierWrapper==nullptr){
        return false;
    }
    minPacket.identifierField.AddIdentifier(identifierWrapper);
    return true;
}
bool Interest::FillDataToMINPacket(){
    return this->DoFillDataToMINPacket(this->minPacket);
}

bool Interest::DoExtraDataFromMINPacket(MINPacket& minPacket){
    mindev::encoding::Block block=minPacket.mutableField.mutableProtectField.GetBlockByType(mindev::encoding::VlInt::VlInt(mindev::encoding::TLV.TlvCongestionMark));
    if(!this->congestionMark.WireDecode(block)){
        return false;
    }
    block =minPacket.mutableField.mutableDangerousField.GetBlockByType(mindev::encoding::VlInt::VlInt(mindev::encoding::TLV.TlvTTL));
    if(!this->ttl.WireDecode(block)){
        return false;
    }
    block =minPacket.mutableField.mutableDangerousField.GetBlockByType(mindev::encoding::VlInt::VlInt(mindev::encoding::TLV.TlvIncomingLogicFaceId));
    if(!this->incomingLogficFaceId.WireDecode(block)){
        return false;
    }
    //解析只读区
    mindev::component::ElementContainer elementContainer=minPacket.readonlyField.GetBlocks();
    int len=elementContainer.Length();
    for(int i=0;i<len;i++){
        mindev::encoding::Block newBlock=elementContainer.GetBlock(i);
        int type;
        type=newBlock.GetType().GetVlIntValue2Int();
        switch(type){
            case mindev::encoding::TLV.TlvCanBePrefix:
                if(!this->canBePrefix.WireDecode(newBlock)){
                    return false;
                }
                break;
            case mindev::encoding::TLV.TlvMustBeRefresh:
                if(!this->mustBeRefresh.WireDecode(newBlock)){
                    return false;
                }
                break;
            case mindev::encoding::TLV.TlvInterestLifeTime:
                if(!this->interestLifeTime.WireDecode(newBlock)){
                    return false;
                }
                break;
            case mindev::encoding::TLV.TlvNonce:
                if(!this->nonce.WireDecode(newBlock)){
                    return false;
                }
                break;
            case mindev::encoding::TLV.TlvHopLimit:
                if(!this->hopLimit.WireDecode(newBlock)){
                    return false;
                }
                break;
            case mindev::encoding::TLV.TlvNackHeader:
                if(!this->nackHeader.WireDecode(newBlock)){
                    return false;
                }
                break;
            case mindev::encoding::TLV.TlvPayload:
                if(!this->payload.WireDecode(newBlock)){
                    return false;
                }
                break;
            default:
                break;
        }
    }
    //解析标识区
    mindev::component::IdentifierWrapper identifierWrapper=minPacket.identifierField.GetIdentifierByType(mindev::encoding::VlInt::VlInt(mindev::encoding::TLV.TlvIdentifierContentInterest));
    this->SetName(interestIdentifierWrapper.GetIdentifier());
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
        this->minPacket.packetType=mindev::encoding::VlInt::VlInt(mindev::encoding::TLV.TlvPacketMINManagement);
    }
    else{
        this->minPacket.packetType=mindev::encoding::VlInt::VlInt(mindev::encoding::TLV.TlvPacketMINCommon);
    }
    return this->minPacket.WireEncode(encoder);
}

bool Interest::WireDecode(mindev::encoding::Block& block){
    if(!this->minPacket.WireDecode(block)){
        return false;
    }
    if(this->minPacket.packetType.IsEqual(mindev::encoding::TLV.TlvPacketMINManagement)){
        this->isCommandInterest=true;
    }
}
}

