#include "mindev/include/packet/data.h"
#include "mindev/include/encoding/selfencodingbase.h"
#include "mindev/include/encoding/tlv.h"
#include "mindev/include/encoding/elementcontainer.h"
#include "mindev/include/component/identifierwrapper.h"

namespace mindev::component{
    template<typename T>
    IdentifierWrapper BuildIdentifierWrapper(T&& val,decltype(mindev::encoding::TLV::TlvInvalid) flag);
};
namespace mindev::packet{
    Data::Data(const mindev::component::Identifier& name,const mindev::component::Payload& payload,const mindev::component::FreshnessPeriod& freshnessPeriod,const mindev::component::NoCache& noCache,const mindev::component::CongestionMark congestionMark,const mindev::component::TTL& ttl){
        this->name=name;
        this->payload=payload;
        this->freshnessPeriod=freshnessPeriod;
        this->noCache=noCache;
        this->ttl=ttl;
    }
    std::optional<Data> Data::CreateDataByMINPacket(MINPacket& minPacket){
        Data data;
        data.minPacket.signatureField.SetSignatures(minPacket.signatureField.GetSignatures());
        if (!data.DoExtraDataFromFields(minPacket)) {
            return std::nullopt;
        }
        return data;
    
    }
    std::string Data::ToUri(){
        return this->name.ToUri();
    }

    void Data::SetNameByString(const std::string& name){
        auto tmp = component::Identifier::BuildIdentifierByString(name);
        if(tmp.has_value()){
            this->name = tmp.value();
        }
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
        std::optional<mindev::encoding::Block> block=mindev::encoding::SelfEncodingBase().SelfWireEncode(this->congestionMark);
        if (!block) {
            return false;
        }
        minPacket.mutableField.mutableProtectField.AddBlock(*block);
        //填充可变非保护区
        minPacket.mutableField.mutableDangerousField.ClearBlocks();
        // TTL
        block =mindev::encoding::SelfEncodingBase().SelfWireEncode(this->ttl);
        if (block == std::nullopt) {
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
        if (this->freshnessPeriod.isInitial()) {
            block=mindev::encoding::SelfEncodingBase().SelfWireEncode(this->freshnessPeriod);
            if (block==std::nullopt) {
                return false;
            }
            minPacket.readOnlyField.AddBlock(*block);
        }
        //noCache
        if (this->noCache.isInitial()) {
            block=mindev::encoding::SelfEncodingBase().SelfWireEncode(this->noCache);
            if (block==std::nullopt) {
                return false;
            }
            minPacket.readOnlyField.AddBlock(*block);
        }
        //Payload
        if (!this->payload.GetValue().empty()) {
            block=mindev::encoding::SelfEncodingBase().SelfWireEncode(this->payload);
            if (block==std::nullopt) {
                return false;
            }
            minPacket.readOnlyField.AddBlock(*block);
        }
        /////////////////////////////////////////////////////////////
        //// 填充标识区
        /////////////////////////////////////////////////////////////
        minPacket.identifierField.ClearIdentifiers();
        auto identifierWrapper= component::BuildIdentifierWrapper<mindev::component::IdentifierComponentContainer>(this->name.GetComponents(),mindev::encoding::TLV::TlvIdentifierContentInterest);
        if(!identifierWrapper.IsValid()){
            return false;
        }
        minPacket.identifierField.AddIdentifier(identifierWrapper);
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
        auto block = minPacket.mutableField.mutableProtectField.GetFirstBlockByType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvCongestionMark));
        if(!block){
            return false;
        }else{
            if(!this->congestionMark.WireDecode(*block)){
                return false;
            }
        }
        //ttl
        block=minPacket.mutableField.mutableDangerousField.GetFirstBlockByType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvTTL));
    if(!block){
        return false;
    }else{
        if(!this->ttl.WireDecode(*block)){
            return false;
        }
    }
        /////////////////////////////////////////////////////////////
                //// 解析只读区
                //             {                             => 只读区
                //                 [FreshnessPeriod]
                //                 <Payload>
                //             }
                /////////////////////////////////////////////////////////////
        for(auto elem:minPacket.readOnlyField.GetBlocks().GetElements()){
            auto type = bigint::_bigint_to<int>(elem.GetType().GetVlIntValue());
            switch (type){
                case mindev::encoding::TLV::TlvFreshnessPeriod:
                    if(!this->freshnessPeriod.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvPayload:
                    if(!this->payload.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvNoCache:
                    if(!this->noCache.WireDecode(elem)){
                        return false;
                    }
                    break;
                default:
                    break;
            }
            }
        //解析标识区
        auto identifierWrapper=minPacket.identifierField.GetIdentifierByType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifierContentData));
        if(!identifierWrapper.has_value()){
            return false;
        }
        this->name=identifierWrapper.value().GetIdentifier();
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
        this->minPacket.packetType=mindev::encoding::VlInt(mindev::encoding::TLV::TlvPacketMINCommon);
        return this->minPacket.WireEncode(encoder);
    }
    bool Data::WireDecode(mindev::encoding::Block& block){
        if(!this->minPacket.WireDecode(block)){
            return false;
        }
        return this->ExtraDataFromFields();
    }
}
