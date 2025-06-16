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
#include <optional>
namespace mindev::encoding{
    class Block;
    class Encoder;
}
namespace mindev::packet{
    class CPacket:public InteractWithField,public mindev::encoding::IEncodingAble{
    public:
        MINPacket minPacket;
        mindev::component::TTL ttl;
        mindev::component::Payload payload;
        mindev::component::Identifier srcIdentifier;
        mindev::component::Identifier dstIdentifier;
        std::vector<char> rawData; //CPacket编码后的数据
        CPacket(){};
        CPacket(const mindev::component::Identifier& srcIdentifier,const mindev::component::Identifier& dstIdentifier ,const mindev::component::Payload& payload,const mindev::component::TTL& ttl);
        std::vector<char>& GetRawData(){return this->rawData;};
        /**
         * @Description: 编码CPacket
         */    
        bool EncodeSelf();
        std::optional<CPacket> CreateCPacketByMINPacket(const MINPacket& minpacket);
        /**
         * @Description: 获取、设置源标识
         */    
        mindev::component::Identifier& GetSrcIdentifier(){return this->srcIdentifier;};
        void SetSrcIdentifier(const mindev::component::Identifier& srcIdentifier){this->srcIdentifier = srcIdentifier;};
        /**
         * @Description: 获取、设置目的标识
         */    
        mindev::component::Identifier& GetDstIdentifier(){return this->dstIdentifier;};
        void SetDstIdentifier(const mindev::component::Identifier& dstIdentifier){this->dstIdentifier = dstIdentifier;};
        /**
         * @Description: 获取、设置TTL
         */    
        mindev::component::TTL& GetTtl() {return this->ttl;};
        void SetTtl(const mindev::component::TTL& ttl){this->ttl = ttl;};
        /**
         * @Description: 展示目的标识
         */
        inline std::string ToUri() { return this->dstIdentifier.ToUri();}
        /**
         * @Description: 获取pyload中的value
         */    
        inline std::vector<char>& GetValue(){
            return this->payload.GetValue();
        }
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
        bool DoExtraDataFromFields(const MINPacket& minPacket);
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
