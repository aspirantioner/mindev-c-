#include "mindev/include/logicface/linkservice.h"
#include "mindev/include/component/identifier.h"
#include "mindev/include/packet/cpacket.h"
#include "mindev/include/packet/lppacket.h"
#include <climits>
#include "mindev/include/encoding/sizet.h"
#include "mindev/include/encoding/encoder.h"
#include <optional>
#include <vector>

namespace mindev::logicface {
bool LinkService::Init(int mtu) {

    static const std::string server_str = "/testsrc";
    static const long ttl_val = 64;
    static const int payload_len = 1000;
    static const int cpacket_len = 100000;

    this->mtu = mtu;
    if (!this->CalculateLpPacketHeadSize()) {
        return false;
    };
    this->lpPacketId = 0;
    auto serverIden = mindev::component::Identifier::BuildIdentifierByString(server_str);
    if (!serverIden.has_value()) {
        return false;
    }
    mindev::packet::CPacket cPacket;
    cPacket.SetSrcIdentifier(serverIden.value());
    cPacket.SetDstIdentifier(serverIden.value());
    cPacket.ttl.SetTtl(64);
    cPacket.payload.SetValue(std::vector<char>(payload_len, 0));
    mindev::encoding::Encoder encoder;
    if (!encoder.EncoderReset(mindev::encoding::SizeT(mindev::encoding::Encoder::MaxPacketSize),
                              mindev::encoding::SizeT(0))) {
        return false;
    }
    if (cPacket.WireEncode(encoder) == -1) {
        return false;
    }
    this->cpacketBytes = encoder.GetBuffer();
    return true;
}
bool LinkService::CalculateLpPacketHeadSize() {
    mindev::packet::LpPacket lppacket;
    lppacket.lpPacketHeader.SetLpPacketFragmentId(mindev::component::LpPacketFragmentId(LONG_MAX));
    lppacket.lpPacketHeader.SetLpPacketFragmentSeq(mindev::component::LpPacketFragmentSeq(LONG_MAX));
    lppacket.lpPacketHeader.SetLpPacketFragmentNum(mindev::component::LpPacketFragmentNum(LONG_MAX));
    lppacket.SetValue(std::vector<char>(mindev::encoding::Encoder::MaxPacketSize, 0));
    mindev::encoding::Encoder encoder;
    if (!encoder.EncoderReset(mindev::encoding::SizeT(mindev::encoding::Encoder::MaxPacketSize + LpPacketHeaderMaxSize),
                              mindev::encoding::SizeT(0))) {
        return false;
    }
    this->lpPacketHeadSize = lppacket.WireEncode(encoder);
    this->lpPacketHeadSize -= mindev::encoding::Encoder::MaxPacketSize;
    return false;
}
std::optional<mindev::packet::MINPacket>
LinkService::GetMINPacketFromLpPacket(const mindev::packet::LpPacket &lpPacket) {
    std::vector<char> payloaod = lpPacket.payload.Getvalue();
    mindev::encoding::Block block(payload, true);
    mindev::packet::MINPacket minPacket;
    if (!minPacket.WireDecode(block)) {
        return std::nullopt;
    }
    return minPacket;
}
bool LinkService::SendFragment(const std::vector<char> &buf, int bufLen, long fragmentId, long fragmentNum,
                               long fragmentSeq) {
    if (bufLen < 0 || bufLen > buf.size()) {
        return false; // 或抛出异常
    }
    if (!this->transport) {
        return false;
    }
    mindev::packet::LpPacket lpPacket;
    lpPacket.SetId(fragmentId);
    lpPacket.SetFragmentNum(fragmentNum);
    lpPacket.SetFragmentSeq(fragmentSeq);
    std::vector<char> nbuf(buf.begin(), buf.begin() + bufLen);
    lpPacket.SetValue(nbuf);
    return this->transport->Send(lpPacket);
}
bool LinkService::SendByteBuffer(const std::vector<char> &buf, int bufLen) {
    int fragmentLen = this->mtu - this->lpPacketHeadSize - 10;
    int startIndex = 0;
    long fragmentSeq = 0;
    long fragmentNum = bufLen / fragmentLen;
    if (bufLen % fragmentLen != 0) {
        fragmentNum++;
    }
    while (startIndex < bufLen) {
        if (fragmentLen > (bufLen - startIndex)) {
            fragmentLen = bufLen - startIndex;
        }
        std::vector<char> nbuf(buf.begin() + startIndex, buf.begin() + startIndex + fragmentLen);
        if (!this->SendFragment(nbuf, fragmentLen, this->lpPacketId, fragmentNum, fragmentSeq)) {
            return false;
        }
        startIndex += fragmentLen;
        fragmentSeq++;
    }
    this->lpPacketId++;
    return true;
}
mindev::packet::LpPacket &LinkService::GetLpPacketFromQuickCPacket(const std::vector<char> &encodedBytes) {
    mindev::packet::LpPacket lpPacket;
    ;
    lpPacket.SetId(this->lpPacketId);
    lpPacket.SetFragmentNum(1);
    lpPacket.SetFragmentSeq(0);
    lpPacket.SetValue(encodedBytes);
    this->lpPacketId++;
    return lpPacket;
}
std::optional<mindev::packet::LpPacket> LinkService::GetLpPacketFromCPacket(const mindev::packet::CPacket &cPacket) {
    // 1.CPacket => byte[]
    mindev::encoding::Encoder encoder;
    if (!encoder.EncoderRest(mindev::encoding::SizeT(mindev::encoding::Encoder::MaxPacketSize),
                             mindev::encoding::SizeT(0))) {
        return std::nullopt;
    }
    int bufLen = const_cast<mindev::packet::CPacket &>(cPacket).WireEncode(encoder);
    std::vector<char> buf = encoder.GetBuffer();
    // 2.byte[] => LpPacket
    mindev::packet::LpPacket lpPacket;
    lpPacket.SetId(this->lpPacketId);
    lpPacket.SetFragmentNum(1); // 分片数
    lpPacket.SetFragmentSeq(0); // 片序号
    lpPacket.SetValue(buf);
    this->lpPacketId++;
    return lpPacket;
}
} // namespace mindev::logicface