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
#include "MINPacket.h"
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
        const std::vector<char>& getRawData() const;
        /**
         * @Description: 编码CPacket
         */    
        bool encodeSelf();
        CPacket createCPacketByMINPacket(MINPacket& minpacket);
        /**
         * @Description: 获取、设置源标识
         */    
        const mindev::component::Identifier& getSrcIdentifier() const;
        void setSrcIdentifier(mindev::component::Identifier& srcIdentifier);
        /**
         * @Description: 获取、设置目的标识
         */    
        const mindev::component::Identifier& getDstIdentifier() const;
        void setDstIdentifier(mindev::component::Identifier& dstIdentifier);
        /**
         * @Description: 获取、设置TTL
         */    
        const mindev::component::TTL& getTtl() const;
        void setTtl(mindev::component::TTL& ttl);
        /**
         * @Description: 展示目的标识
         */    
        std::string toUri();
        /**
         * @Description: 获取pyload中的value
         */    
        const std::vector<char>& getValue() const;
        /**
         * @Description: 将CPacket的各项属性填充到目标MINPacket中定义的对应分区当中
         * @param {MINPacket*} minPacket
         */    
        bool doFillDataToFields(MINPacket& minPacket);
        /**
         * @Description: 将CPacket中的各项属性填充到本对象的minPacket的对应分区
         */    
        bool fillDataToFields();
        /**
         * @Description: 从minPacket的对应分区中提取CPacket的各项属性
         * @param {MINPacket*} minPacket
         */    
        bool doExtraDataFromFields(MINPacket& minPacket);
        /**
         * @Description: 从本对象的minPacket中提取CPacket的各项属性
         */    
        bool extraDataFromFields();
        /**
         * @Description:将CPacket编码成TLV
         */    
        int wireEncode(mindev::encoding::Encoder& encoder);
        /**
         * @Description: 从tlv块中解码出一个CPacket
         * @param {Block*} block
         */    
        bool wireDecode(mindev::encoding::Block& block);
    };
}

#endif
