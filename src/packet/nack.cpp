#include "mindev/include/packet/nack.h"
namespace mindev::packet{
    Nack::Nack(){
        this->interest = Interest();
    };
    Nack::Nack(Interest& interest,long reason){
        this->interest = interest;
        this->SetNackReason(reason);
    };
    std::unique_ptr<Nack> Nack::CreateNackByInterest(Interest& interest){
        if(!interest.nackHeader.IsInitial()){
            //NackHeader 没有初始化
            return nullptr;
        }
        std::unique_ptr<Nack> nack = std::make_unique<Nack>(interest,interest.nackHeader.GetNackReason());
        return nack;
    }
    std::unique_ptr<Nack> Nack::CreateNackByMINpacket(MINPacket& minPacket){
        std::unique_ptr<Interest> interest = Interest().CreateInterestByMINPacket(minPacket);
        if(interest == nullptr){
            return nullptr;
        }
        else{
            return this->CreateNackByInterest(*interest);
        }
    }
    void Nack::SetNackReason(long reason){
        this->interest.nackHeader.SetNackReason(reason);
    }
    long Nack::GetNackReason() const{
        return this->interest.nackHeader.GetNackReason();
    }
    int Nack::WireEncode(mindev::encoding::Encoder& encoder){
        return this->interest.WireEncode(encoder);
    }
    bool Nack::WireDecode(mindev::encoding::Block& block){
        return this->interest.WireDecode(block);
    }

}