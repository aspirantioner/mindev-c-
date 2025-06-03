#include "mindev/include/packet/data.h"
#include "mindev/include/encoding/selfencodingbase.h"
#include "mindev/include/encoding/TLV.h"
#include "mindev/include/component/elementcontainer.h"
#include "mindev/include/component/identifierwrapper.h"
namespace mindev::packet{
Data::Data():minPacket(MINPacket()),freshnessPeriod(mindev::component::FreshnessPeriod()),noCache(mindev::component::NoCache()),payload(mindev::component::Payload()),congestion(mindev::component::Congestion()),ttl(mindev::component::TTL()),name(mindev::component::Identifier()){};
Data::Data(mindev::component::Identifier& name,mindev::component::Payload& payload,mindev::component::FreshnessPeriod& freshnessPeriod,mindev::component::NoCache& noCache,mindev::component::CongestionMark congestionMark,mindev::component::TTL& ttl){
    this->name=name;
    this->payload=payload;
    this->freshnessPeriod=freshnessPeriod;
    this->noCache=noCache;
    this->ttl=ttl;
}
std::unique_ptr<Data> Data::CreateDataByMINPacket(MINPacket& minPacket){
    std::unique<Data> data=std::make_unique<Data>();
    data->minPacket.signatureField.SetSignatures(minPacket.signatureField.GetSignatures());
    if (!data->DoExtraDataFromFields(minPacket)) {
        return nullptr;
    }
    return data;

}
std::string Data::ToUir(){
    return this->name.ToUri();
}
mindev::component::Identifier& Data::GetName() const{return this->name;}

void Data::SetName(mindev::component::Identifier& name){this->name=name;}

void Data::SetNameByString(sdt::string& name){
    this->name=mindev::component::Identifier(name);
}
bool Data::DoFillDataToFields(MINPacket& minPacket){
            /////////////////////////////////////////////////////////////
        //// 填充可变区
        //             {                             => 可变区
        //                 {                         => 受保护区
        //                     [CongestionMark]
        //                 }
        //                 {                         => 非受保护区
        //                     "Empty"
        //                 }
        //             }
        /////////////////////////////////////////////////////////////\
    //填充可变保护区
    minPacket.mutableField.mutableProtectField.ClearBlocks();
    //congestionMark
    std::unique_ptr<Block> block=mindev::encoding::SelfEncodingBase().SelfWireEncode(this->congestionMark);
    if (block==nullptr) {
        return false;
    }
    minPacket.mutableField.mutableProtectField.AddBlock(*block);
    //填充可变非保护区
    minPacket.mutableField.mutableDangerousField.ClearBlocks();
    // TTL
    block =mindev::encoding::SelfEncodingBase().selfWireEncode(this->ttl);
    if (block == nullptr) {
        return false;
    }
    minPacket.mutableField.mutableDangerousField.AddBlock(*block);
    /////////////////////////////////////////////////////////////
    //// 填充只读区
    //             {                             => 只读区
    //                 [FreshnessPeriod]
    //				   [NackHeader]
    //                 <Payload>
    //             }
    /////////////////////////////////////////////////////////////
    minPacket.readOnlyField.ClearBlocks();
    //freshnessPeriod
    if (this->freshnessPeriod.IsInitial()) {
        block=mindev::encoding::SelfEncodingBase().selfWireEncode(this->freshnessPeriod);
        if (block==nullptr) {
            return false
        }
        minPacket.readOnlyField.AddBlock(*block);
    }
    //noCache
    if (this->noCache.IsInitial()) {
        block=mindev::encoding::SelfEncodingBase().SelfWireEncode(this->noCache);
        if (block==nullptr) {
            return false;
        }
        minPacket.readOnlyField.AddBlock(*block);
    }
    //Payload
    if (!this->payload.GetValue().Empty()) {
        block=mindev::encoding::SelfEncodingBase().SelfWireEncode(this->payload);
        if (block==nullptr) {
            return false;
        }
        minPacket.readOnlyField.AddBlock(*block);
    }
    /////////////////////////////////////////////////////////////
    //// 填充标识区
    /////////////////////////////////////////////////////////////
    minPacket.identifierField.ClearIdentifiers();
    std::make_unique<mindev::component::IdentifierWrapper> identifierWrapper=mindev::component::IdentifierWrapper().CreateContentDataIdentifierByComponents(this->name.GetComponents());
    if(identifierWrapper==nullptr){
        return false;
    }
    minPacket.identifierField.AddIdentifier(*identifierWrapper);
    return true;
}
    /**
     * 将 Data 的各项属性填充到 MINPacket 中定义的对应分区当中
     *
     * @return
     */
bool Data::FillDataToFields(){
    return this->DoFillDataToFields(this->minPacket);
}

bool Data::DoExtraDataFromFields(MINPacket& minPacket){
                /////////////////////////////////////////////////////////////
            //// 解析可变区
            //             {                             => 可变区
            //                 {                         => 受保护区
            //                     [CongestionMark]
            //                 }
            //                 {                         => 非受保护区
            //                     [TTL]
            //                 }
            //             }
            /////////////////////////////////////////////////////////////
    //congestionMark
    mindev::encoding::Block block minPacket.mutableField.mutableProtectField.GetBlockByType(mindev::encoding::VlInt::VlInt(mindev::encoding::TLV.TlvCongestionMark));
    if(!this->congestionMark.WireDecode(block)){
        return false;
    }
    //ttl
    block=minPacket.mutableField.mutableDangerousField.GetBlockByType(mindev::encoding::VlInt::VlInt(mindev::encoding::TLV.TlvTTL));
    if(!this->ttl.WireDecode(block)){
        return false;
    }
    /////////////////////////////////////////////////////////////
            //// 解析只读区
            //             {                             => 只读区
            //                 [FreshnessPeriod]
            //                 <Payload>
            //             }
            /////////////////////////////////////////////////////////////
    mindev::component::ElementContainer elementContainer=minpacket.readOnlyField.GetBlocks();
    int len=elementContainer.Length();
    for(int i=0;i<len;i++){
        mindev::encoding::Block newBlock=elementContainer.GetBlock(i);
        int type=newBlock.GetType().GetVlIntValue2Int();
        switch (type){
            case mindev::encoding::TLV.TlvFreshnessPeriod:
                if(!this->freshnessPeriod.WireDecode(newBlock)){
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
    mindev::component::IdentifierWrapper identifierWrapper=minpacket.identifierField.GetIdentifierByType(mindev::encoding::VlInt::VlInt(mindev::encoding::TLV.TlvIdentifierContentData));
    this->name=identifierWrapper.GetIdentifier();
    return true;
}
bool Data::ExtraDataFromFields(){
    return this->DoExtraDataFromFields(this->minPacket);
}
int Data::WireEncode(mindev::encoding::Encoder& encoder){
    //首先将各项属性填充到分区当中
    if(!this->FillDataToFields()){
        return -1;
    }
    //指定包类型
    this->minPacket.packetType=mindev::encoding::VlInt::VlInt(mindev::encoding::TLV.TlvPacketMINCommon);
    return this->minPacket.WireEncode(encoder);
}
bool Data::WireDecode(mindev::encoding::Block& block){
    if(!this->minPacket.WireDecode(block)){
        return false;
    }
    return this->ExtraDataFromFields();
}
}
