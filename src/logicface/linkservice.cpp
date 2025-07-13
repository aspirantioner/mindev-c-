#include "mindev/include/logicface/linkservice.h"
#include "mindev/include/component/identifier.h"
#include "mindev/include/packet/cpacket.h"
#include "mindev/include/packet/lppacket.h"
#include <climits>

namespace mindev::logicface {
    bool LinkService::Init(int mtu){

        static const std::string  server_str = "/testsrc";
        static const long ttl_val = 64;
        static const int payload_len = 1000;
        static const int cpacket_len = 100000;
        
        this->mtu = mtu;
        if(!this->CalculateLpPacketHeadSize()){
            return false;
        };
        this->lpPacketId = 0;
        auto serverIden = mindev::component::Identifier::BuildIdentifierByString(server_str);
        if(!serverIden.has_value()){
            return false;
        }
        mindev::packet::CPacket cPacket;
        cPacket.SetSrcIdentifier(serverIden.value());
        cPacket.SetDstIdentifier(serverIden.value());
        cPacket.ttl.SetTtl(64);
        cPacket.payload.SetValue(std::vector<char>(payload_len,0));
        mindev::encoding::Encoder encoder;
        if(!encoder.EncoderReset(mindev::encoding::SizeT(mindev::encoding::Encoder::MaxPacketSize), mindev::encoding::SizeT(0))){
            return false;
        }
        if(cPacket.WireEncode(encoder)==-1){
            return false;
        }
        this->cpacketBytes = encoder.GetBuffer();
        return true;
    }
    bool LinkService::CalculateLpPacketHeadSize(){
        mindev::packet::LpPacket lppacket;        
        lppacket.lpPacketHeader.SetLpPacketFragmentId(mindev::component::LpPacketFragmentId(LONG_MAX));
        lppacket.lpPacketHeader.SetLpPacketFragmentSeq(mindev::component::LpPacketFragmentSeq(LONG_MAX));
        lppacket.lpPacketHeader.SetLpPacketFragmentNum(mindev::component::LpPacketFragmentNum(LONG_MAX));
        lppacket.SetValue(std::vector<char>(mindev::encoding::Encoder::MaxPacketSize,0));
        mindev::encoding::Encoder encoder;
        if(!encoder.EncoderReset(mindev::encoding::SizeT(mindev::encoding::Encoder::MaxPacketSize+LpPacketHeaderMaxSize), mindev::encoding::SizeT(0))){
            return false;
        }
        this->lpPacketHeadSize = lppacket.WireEncode(encoder);
        this->lpPacketHeadSize -= mindev::encoding::Encoder::MaxPacketSize;
        return false;
    }
}