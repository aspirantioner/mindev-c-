//
// 表示一个通用的MIN推式包
//
// @Description:
//	1. 包格式定义如下：
//		CPacket = 5 TLV-LENGTH
//             {                             => 标识区
//               SrcIdentifier  => 源标识
//               DstIdentifier  => 目的标识
//             }
//             { Signature }                 => 签名区
//             {                             => 只读区
//                 <Payload>
//             }
//             {                             => 可变区
//                 {                         => 受保护区
//                     "Empty"
//                 }
//                 {                         => 非受保护区
//                     [TTL]
//                 }
//             }
//
#ifndef CPACKET_H_
#define CPACKET_H_
#include "minpacket.h"
#include "interactwithfield.h"
#include "mindev/include/encoding/iencodingable.h"
#include "mindev/include/component/ttl.h"
#include "mindev/include/component/payload.h"
#include "mindev/include/component/identifier.h"
#include <vector>
#include <string>
namespace mindev::encoding{
    class Block;
    class Encoder;
}
namespace mindev::packet{
    class CPacket:public InteractWithField,public IEncodingAble{
    public:
        MINPacket minPacket;
        mindev::component::TTL ttl;
        mindev::component::Payload payload;
        mindev::component::Identifier srcIdentifier;
        mindev::component::Identifier dstIdentifier;
        std::vector<char> rawData; //CPacket编码后的数据
        CPacket();
        CPacket(mindev::component::Identifier srcIdentifier,mindev::component::Identifier dstIdentifier ,mindev::component::Payload payload,mindev::component::TTL ttl);
        ~CPacket();
        std::vector<char>& GetRawData() const;
        /**
         * @Description: 编码CPacket
         */    
        bool EncodeSelf();
        CPacket CreateCPacketByMINPacket(MINPacket& minpacket);
        /**
         * @Description: 获取、设置源标识
         */    
        mindev::component::Identifier& GetSrcIdentifier() const;
        void SetSrcIdentifier(mindev::component::Identifier& srcIdentifier);
        /**
         * @Description: 获取、设置目的标识
         */    
        mindev::component::Identifier& GetDstIdentifier() const;
        void SetDstIdentifier(mindev::component::Identifier& dstIdentifier);
        /**
         * @Description: 获取、设置TTL
         */    
        mindev::component::TTL& GetTtl() const;
        void SetTtl(mindev::component::TTL& ttl);
        /**
         * @Description: 展示目的标识
         */    
        std::string ToUri();
        /**
         * @Description: 获取pyload中的value
         */    
        std::vector<char>& GetValue() const;
        /**
         * @Description: 将CPacket的各项属性填充到目标MINPacket中定义的对应分区当中
         * @param {MINPacket*} minPacket
         */    
        bool DoFillDataToFields(MINPacket& minPacket);
        /**
         * @Description: 将CPacket中的各项属性填充到本对象的minPacket的对应分区
         */    
        bool FillDataToFields();
        /**
         * @Description: 从minPacket的对应分区中提取CPacket的各项属性
         * @param {MINPacket*} minPacket
         */    
        bool DoExtraDataFromFields(MINPacket& minPacket);
        /**
         * @Description: 从本对象的minPacket中提取CPacket的各项属性
         */    
        bool ExtraDataFromFields();
        /**
         * @Description:将CPacket编码成TLV
         */    
        int WireEncode(mindev::encoding::Encoder& encoder);
        /**
         * @Description: 从tlv块中解码出一个CPacket
         * @param {Block*} block
         */    
        bool WireDecode(mindev::encoding::Block& block);
    };
}

#endif
