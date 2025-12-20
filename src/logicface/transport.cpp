#include "mindev/include/logicface/transport.h"

namespace mindev::logicface {
    std::optional<mindev::packet::LpPacket> Transport::ParseByteArrayToLpPacket(std::vector<char>& buf){
        auto block = mindev::encoding::Block::DebugCreateBlockByBuffer(buf, true);
        if(!block.has_value()){
            return std::nullopt;
        }
        mindev::packet::LpPacket lpPacket;
        if(!lpPacket.WireDecode(block.value())){
            return std::nullopt;
        }
        return lpPacket;
    }
    std::vector<char> Transport::EncodeLpPacketToByteArray(mindev::packet::LpPacket& lpPacket){
        mindev::encoding::Encoder encoder;
        encoder.EncoderReset(mindev::encoding::SizeT(mindev::encoding::Encoder::MaxPacketSize), mindev::encoding::SizeT(0));
        int encodeBufLen = lpPacket.WireEncode(encoder);
        if(encodeBufLen<0){
            return std::vector<char>();
        }
        return encoder.GetBuffer();
    }
}