#include "mindev/include/logicface/streamtransport.h"
#include "mindev/include/logicface/logicface.h"
#include <bits/alltypes.h>

namespace mindev::logicface {
    bool StreamTransport::Send(mindev::packet::LpPacket& lpPacket){
        auto encodeBuf = this->EncodeLpPacketToByteArray(lpPacket);
        auto tmp = this->ParseByteArrayToLpPacket(encodeBuf);
        if(tmp.has_value()){
            if(auto link = this->linkService.lock()){
                auto min = link->GetMINPacketFromLpPacket(tmp.value());
                if(min.has_value()){
                    int a = 0;
                }
            }
        }
        if(encodeBuf.empty()){
            return false;
        }
        int writeLen = 0;
        while(writeLen < encodeBuf.size()){
            auto writeRet = this->m_scoket_channel->Write(encodeBuf,writeLen,encodeBuf.size()-writeLen);
            if(writeRet<0){
                if(auto tmp = this->linkService.lock()){
                    if(auto logicface = tmp->logicFace.lock()){
                        logicface->ShutDown();
                    }
                }
                return false;
            }
            writeLen+=writeRet;
        }
        return true;
    }
    std::pair<long,mindev::packet::LpPacket> StreamTransport::ReadPktAndDeal(const std::vector<char>& buf,long buflen){
        if(buflen<mindev::encoding::VlInt(mindev::encoding::TLV::TlvLpPacket).GetSize()){
            return std::make_pair<long, mindev::packet::LpPacket>(0,mindev::packet::LpPacket());
        }
        mindev::encoding::VlInt pktType = mindev::encoding::TLV::ReadType(buf, mindev::encoding::VlInt(0));
        if(bigint::_bigint_to<int>(pktType.GetVlIntValue()) != mindev::encoding::TLV::TlvLpPacket){
            return std::make_pair<long, mindev::packet::LpPacket>(0,mindev::packet::LpPacket());
        }
        if(auto tmp = this->linkService.lock()){
            if(buflen<tmp->lpPacketHeadSize){
                return std::make_pair<long, mindev::packet::LpPacket>(0,mindev::packet::LpPacket());
            }    
        }
        
        int pktTypeLen = pktType.GetSize();
        int pktLen =bigint::_bigint_to<int>(mindev::encoding::TLV::ReadVarNumber(buf, mindev::encoding::VlInt(pktTypeLen)).GetVlIntValue());
        int totalPktLen = pktTypeLen+mindev::encoding::VlInt(pktLen).GetSize()+pktLen;
        if(buflen>=totalPktLen){
            auto tmp = std::vector<char>(buf.begin(),buf.begin()+totalPktLen);
            auto lpPacket = this->ParseByteArrayToLpPacket(tmp);
            if(lpPacket.has_value()){
                return std::pair<long, mindev::packet::LpPacket>(totalPktLen, lpPacket.value());
            }
        }
        return std::make_pair<long, mindev::packet::LpPacket>(0,mindev::packet::LpPacket());
    }
    mindev::packet::LpPacket StreamTransport::DoReceive(){
        auto packetpair = this->ReadPktAndDeal(std::vector<char>(this->recBuf.begin(),this->recBuf.begin()+this->recvLen), this->recvLen);
        auto pktLen = packetpair.first;
        auto lpPacket = packetpair.second;
        if(pktLen>0){
            std::copy(this->recBuf.begin()+pktLen, this->recBuf.end(), this->recBuf.begin());
            this->recvLen-=pktLen;
        }
        return lpPacket;
    }
    std::optional<mindev::packet::LpPacket> StreamTransport::Receive(){
        while(true){
            auto lpPacket = this->DoReceive();
            if(!lpPacket.GetValue().empty()){
                return lpPacket;
            }
            auto recvRet = this->m_scoket_channel->Read<char>(this->recBuf,this->recvLen);
            if(recvRet<=0){
                return std::nullopt;
            }
            this->recvLen += recvRet;
        }
    }
    bool StreamTransport::SetReadTimeout(long duration){
        if(duration <= 0 ){
            return true;
        }

        struct timeval timeout;
        timeout.tv_sec = duration / 1000;
        timeout.tv_usec = (duration % 1000)*1000;
        
        if(setsockopt(this->m_scoket_channel->GetFd(), SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout))<0){
            return false;
        }    

        return true;
    }
}