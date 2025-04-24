//
// 表示一个MIN拉取式数据包
//
// @Description:
// 	1. 包格式的定义如下
//		Data = 7 TLV-LENGTH
//             { DataIdentifier }            => 标识区
//             { Signature }                 => 签名区
//             {                             => 只读区
//                 [FreshnessPeriod]
//				   [NoCache]
//                 <Payload>
//             }
//             {                             => 可变区
//                 {                         => 受保护区
//                     [CongestionMark]
//                 }
//                 {                         => 非受保护区
//                     [TTL]
//                 }
//             }
//
#ifndef DATA_H_
#define DATA_H_
#include "mindev/include/encoding/iencodingable.h"
#include "interactwithfield.h"
#include <string>
#include "mindev/include/component/ttl.h"
#include "mindev/include/component/payload.h"
#include "mindev/include/component/identifier.h"
#include "mindev/include/component/nocache.h"
#include "mindev/include/component/congestionmark.h"
#include "mindev/include/component/freshnessperiod.h"
#include "MINPacket.h"
namespace mindev::encoding{
    class Block;
    class Encoder;
}

namespace mindev::packet{
    class Data:public IEncodingAble,public InteractWithField{
public:
    MINPacket minPacket;
    mindev::component::FreshnessPeriod freshnessPeriod;
    mindev::component::NoCache noCache;
    mindev::component::Payload payload;
    mindev::component::CongestionMark congestionMark;
    mindev::component::TTL ttl;
    mindev::component::Identifier name;
    Data();
    ~Data();
    Data(mindev::component::Identifier& name,mindev::component::Payload& payload,mindev::component::FreshnessPeriod& freshnessPeriod,mindev::component::NoCache& noCache,mindev::component::CongestionMark congestionMark,mindev::component::TTL& ttl,);
    /**
     * 根据一个 MINPacket 创建一个 Data
     *
     * @return
     */
    Data createDataByMINPacket(MINPacket& minPacket);
    /**
     * 展示数据包的 URI
     *
     * @return
     */
    String toUri();
    /**
     * 获取内容数据包的名字
     *
     * @return
     */
    mindev::component::Identifier getName();
    /**
     * 使用字符串设置数据包的名字
     * @param name
     * @throws PacketException
     */
    void setName(mindev::component::Identifier& name);
    /**
     * 使用字符串设置数据包的名字
     * @param name
     * @throws PacketException
     */
    void setNameByString(String name);
      /**
     * 将 Data 的各项属性填充到 MINPacket 中定义的对应分区当中
     *
     * @return
     */
    bool doFillDataToFields(MINPacket& minPacket);
    /**
     * 将 Data 的各项属性填充到 MINPacket 中定义的对应分区当中
     *
     * @return
     */
    bool fillDataToFields();
    /**
     * 从 MINPacket 的分区中提取出 Data 的各项属性
     *
     * @return
     */
    bool doExtraDataFromFields(MINPacket& minPacket);
    /**
     * 从 MINPacket 的分区中提取出 Data 的各项属性
     *
     * @return
     * @throws PacketException
     */
    bool extraDataFromFields();
    /**
     * 将 Data 线速编码为一个 TLV
     *
     * @param encoder
     * @return
     */
    int wireEncode(mindev::encoding::Encoder& encoder);
    /**
     * 从 TLV Block 中解码出一个 Data
     *
     * @param block
     * @return
     */
    bool wireDecode(mindev::encoding::Block& block);
    };

#endif
