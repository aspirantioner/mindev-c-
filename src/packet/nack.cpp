#include "mindev/include/packet/nack.h"

namespace mindev::packet{
    Nack::Nack(const Interest& interest,long reason){
        this->interest = interest;
        this->SetNackReason(reason);
    };
    std::optional<Nack> Nack::CreateNackByInterest(const Interest& interest){
        if(!interest.nackHeader.isInitial()){
            //NackHeader 没有初始化
            return std::nullopt;
        }
        Nack nack(interest,interest.nackHeader.GetNackReason());
        return nack;
    }
    std::optional<Nack> Nack::CreateNackByMINpacket(const MINPacket& minPacket){
        auto interest = Interest().CreateInterestByMINPacket(minPacket);
        if(!interest){
            return std::nullopt;
        }
        else{
            return this->CreateNackByInterest(*interest);
        }
    }
    void Nack::SetNackReason(long reason){
        this->interest.nackHeader.SetNackReason(reason);
    }
    long Nack::GetNackReason(){
        return this->interest.nackHeader.GetNackReason();
    }
    int Nack::WireEncode(mindev::encoding::Encoder& encoder){
        return this->interest.WireEncode(encoder);
    }
    bool Nack::WireDecode(mindev::encoding::Block& block){
        return this->interest.WireDecode(block);
    }

}