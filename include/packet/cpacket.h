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
#include "TTL.h"
#include "Payload.h"
#include "Identifier.h"
#include <vector>
#include <string>
#include "TLV.h"
namespace mindev::packet{
    class CPacket{
    public:
        MINPacket minPacket;
        TTL ttl;
        Payload payload;
        Identifier srcIdentifier;
        Identifier dstIdentifier;
        std::vector<unsigned char> rawData; //CPacket编码后的数据
        CPacket();
        CPacket(Identifier srcIdentifier,Identifier dstIdentifier ,Payload payload,TTL ttl);
        ~CPacket();
        const std::vector<unsigned char>& getRawData() const;
        /**
         * @Description: 编码CPacket
         */    
        bool encodeSelf();
        CPacket createCPacketByMINPacket(MINPacket& minpacket);
        /**
         * @Description: 获取、设置源标识
         */    
        const Identifier& getSrcIdentifier() const;
        void setSrcIdentifier(Identifier& srcIdentifier);
        /**
         * @Description: 获取、设置目的标识
         */    
        const Identifier& getDstIdentifier() const;
        void setDstIdentifier(Identifier& dstIdentifier);
        /**
         * @Description: 获取、设置TTL
         */    
        const TTL& getTtl() const;
        void setTtl(TTL& ttl);
        /**
         * @Description: 展示目的标识
         */    
        std::string toUri();
        /**
         * @Description: 获取pyload中的value
         */    
        const std::vector<unsigned char>& getValue() const;
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
        int wireEncode(Encoder& encoder){return 0;};
        /**
         * @Description: 从tlv块中解码出一个CPacket
         * @param {Block*} block
         */    
        bool wireDecode(Block& block){return true;};
    };
}

#endif
