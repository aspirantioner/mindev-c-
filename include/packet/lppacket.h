#ifndef LPPACKET_H_
#define LPPACKET_H_
#include <vector>
#include "mindev/include/component/lppacketheader.h"
#include "mindev/include/component/payload.h"
#include "mindev/include/encoding/encoder.h"
#include "mindev/include/encoding/block.h"

namespace mindev::packet{
    class LpPacket{
private:
    std::vector<char>  rawPayload; //LpPacket转成CPacket，再解码出来的payload
public:
    mindev::component::LpPacketHeader lpPacketHeader;
    mindev::component::Payload payload;
    std::vector<char>& GetRawPayload(){
    return this->rawPayload;
};
    bool DecodeSelf();
    LpPacket(){};
    LpPacket(const mindev::component::LpPacketHeader lpPacketHeader,const mindev::component::Payload payload);
    void SetId(long fragmentId);
    long GetId(){
    return this->lpPacketHeader.GetLpPacketFragmentId().GetId();
    } ;
    void SetFragmentNum(long fragmentNum);
    long GetFragmentNum(){
    return this->lpPacketHeader.GetLpPacketFragmentNum().GetFragmentNum();
    };
    void SetFragmentSeq(long fragmentSeq);
    long GetFragmentSeq(){
    return this->lpPacketHeader.GetLpPacketFragmentSeq().GetFragmentSeq();
};
    void SetValue(const std::vector<char>& value);
    std::vector<char>& GetValue(){
    return this->payload.GetValue();
};
    /**
     * 将 LpPacket 线速编码为一个 TLV
     *
     * @param encoder
     * @return
     * @throws ComponentException
     * @throws PacketException
     */
    int WireEncode(mindev::encoding::Encoder& encoder);
    /**
     * 从 Block TLV 中解码出一个 LpPacket
     *
     * @param block
     * @return
     * @throws ComponentException
     * @throws PacketException
     */
    bool WireDecode(mindev::component::Block& block);

    };
}

#endif /* LPPACKET_H_ */