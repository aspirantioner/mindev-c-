//
// 表示一个通用的 Nack
//
// @Description:
//  Nack 是一个特殊的兴趣包，其就是 Interest 中设置了 NackHeader
//	1. 包格式如下：
//		Nack = 5 TLV-LENGTH
//             { InterestIdentifier }        => 标识区
//             { Signature }                 => 签名区
//             {                             => 只读区
//				   [NackHeader]
//				   ...
//             }
//             {                             => 可变区
//				   ...
//             }
//
#ifndef NACK_H_
#define NACK_H_
#include "mindev/include/encoding/iencodingable.h"
#include "interest.h"
#include "minpacket.h"
#include "mindev/include/encoding/block.h"
#include "mindev/include/encoding/encoder.h"
#include <optional>
namespace mindev::packet{
class Nack:public mindev::encoding::IEncodingAble{
public:
    Interest interest;
    Nack(){};
    Nack(const Interest& interest,long reason);
    /**
     * CreateNackByInterest 通过一个兴趣包构造一个 Nack
     * @param interest
     * @return
     */
    std::optional<Nack> CreateNackByInterest(const Interest& interest);
    /**
     * CreateNackByMINPacket 通过一个 MINPacket 构造一个 Nack
     * @param minPacket
     * @return
     */
    std::optional<Nack> CreateNackByMINPacket(const MINPacket& minPacket);
    /**
     * 设置 Nack 的原因
     */
    void SetNackReason(long reason);
    /**
     * 获取 Nack 的原因
     * @return
     */
    long GetNackReason();
    /**
     * 将 Nack 线速编码为一个 TLV
     * @param encoder
     * @return
     * @throws ComponentException
     * @throws PacketException
     */
    int WireEncode(mindev::encoding::Encoder& encoder) override;
    /**
     * 从 TLV Block 中解码出一个 Nack
     * @param block
     * @return
     * @throws ComponentException
     * @throws PacketException
     */
    bool WireDecode(mindev::encoding::Block& block) override;
};

}





#endif