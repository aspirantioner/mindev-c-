/*
 * @Author: Wang Feng
 * @Description:
 * @Version: 1.0.0
 * @Date: 11:22 2021/3/16
 * @Copyright: MIN-Group；国家重大科技基础设施——未来网络北大实验室；深圳市信息论与未来网络重点实验室
 */
//
// 表示一个通用的内容兴趣包
//
// @Description:
//	1. 包格式如下：
//		Interest = 5 TLV-LENGTH
//             { InterestIdentifier }        => 标识区
//             { Signature }                 => 签名区
//             {                             => 只读区
//                 [CanBePrefix]
//                 [MustBeRefresh]
//                 [InterestLifeTime]
//                 [Nonce]
//                 [HopLimit]
//                 [NackHeader]
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
#ifndef INTEREST_H_
#define INTEREST_H_
#include "interactwithfield.h"
#include "mindev/include/mgmt/controlparameters.h"
#include "minpacket.h"
#include "mindev/include/encoding/iencodingable.h"
#include "mindev/include/component/canbeprefix.h"
#include "mindev/include/component/mustberefresh.h"
#include "mindev/include/component/nonce.h"
#include "mindev/include/component/hoplimit.h"
#include "mindev/include/component/interestlifetime.h"
#include "mindev/include/component/nackheader.h"
#include "mindev/include/component/congestionmark.h"
#include "mindev/include/component/ttl.h"
#include "mindev/include/component/payload.h"
#include "mindev/include/component/incominglogicfaceid.h"
#include "mindev/include/component/identifier.h"
#include "mindev/include/packet/data.h"
#include "mindev/include/encoding/block.h"
#include "mindev/include/encoding/encoder.h"
#include "mindev/include/component/controlparameters.h"
#include <string>
#include <optional>

namespace mindev::packet{
    class Interest:public InteractWithField,public mindev::encoding::IEncodingAble{
public:
    MINPacket minPacket;
    mindev::component::CanBePrefix canBePrefix;
    mindev::component::MustBeRefresh mustBeRefresh;
    mindev::component::InterestLifeTime interestLifeTime;
    mindev::component::Nonce nonce;
    mindev::component::HopLimit hopLimit;
    mindev::component::Payload payload;
    mindev::component::CongestionMark congestionMark;
    mindev::component::TTL ttl;
    mindev::component::NackHeader nackHeader;
    mindev::component::IncomingLogicFaceId incomingLogficFaceId;
    mindev::component::Identifier name;
    bool isCommandInterest=false;
    
    Interest(){};
    Interest(const mindev::component::Identifier& name,const mindev::component::Payload& payload,const mindev::component::InterestLifeTime& interestLifeTime,const mindev::component::CanBePrefix& canBePrefix,const mindev::component::MustBeRefresh& mustBeRefresh,const mindev::component::Nonce& nonce,const mindev::component::HopLimit& hopLimit,const mindev::component::NackHeader& nackHeader,const mindev::component::CongestionMark& congestionMark,const mindev::component::TTL& ttl,const mindev::component::IncomingLogicFaceId& incomingLogficFaceId);
    /**
     * 根据一个 MINPacket 创建一个 Interest
     * @param minPacket
     * @return
     */
    std::optional<Interest> CreateInterestByMINPacket(const MINPacket& minPacket);
    /**
     * 获取内容兴趣包的名字
     *
     * @return
     */
    inline mindev::component::Identifier& GetName(){return this->name;}
    /**
     * 使用字符串设置兴趣包的名字
     * @param name
     * @throws PacketException
     */
    inline void SetName(const mindev::component::Identifier& identifier){this->name = identifier;}
    /**
     * 使用字符串设置兴趣包的名字
     * @param name
     * @throws PacketException
     */
    inline void SetNameByString(const std::string& name){
        auto val = mindev::component::Identifier::BuildIdentifierByString(name);
        if(val.has_value()){
            this->name=val.value();    
        }
    }
    /**
     * 判断一个指定的名字和当前的兴趣包的名字是否匹配
     *
     * @param identifier
     * @return
     */
    bool MatchesName(const mindev::component::Identifier& identifier){return false;};
    /**
     * 判断一个内容兴趣包和一个内容数据包是否匹配
     *
     * @param data
     * @return
     */
    bool MatchesData(const Data& data){return false;};
    /**
     * 判断一个内容兴趣包和当前兴趣包是否匹配
     *
     * @param interest
     * @return
     */
    bool MatchesInterest(const Interest& interest){return false;};
    /**
     * 展示兴趣包的 URI
     *
     * @return
     */
    inline std::string ToUri(){return this->name.ToUri();}
    /**
     * AppendCommandParameters 在名字中添加命令参数字段
     * @param parameters
     * @return
     */
    bool AppendCommandParameters(mindev::mgmt::ControlParameters& parameters){return this->name.AppendCommandParameters(parameters);};
    /**
     * AppendVersionNumber 在名字后面添加一个版本号
     * @param versionNumber
     * @return
     */
    inline bool AppendVersionNumber(long versionNumber){return this->name.AppendVersionNumber(versionNumber);}
    /**
     * AppendFragmentNumber 在名字后面添加一个分片号
     * @param fragmentNumber
     * @return
     */
    inline bool AppendFragmentNumber(long fragmentNumber){return this->name.AppendFragmentNumber(fragmentNumber);};
    /**
     * 将 Interest 的各项属性填充到 MINPacket 中定义的对应分区当中
     *
     * @return
     */
    bool DoFillDataToFields(MINPacket& minPacket);
    /**
     * 将 Interest 的各项属性填充到 MINPacket 中定义的对应分区当中
     * @return
     * @throws PacketException
     */
    bool FillDataToFields() override ;
    /**
     * 从 MINPacket 的分区中提取出 Interest 的各项属性
     *
     * @return
     */
    bool DoExtraDataFromFields(MINPacket& minPacket);
    bool ExtraDataFromFields() override ; 
    /**
     * 将 Interest 线速编码为一个 TLV
     *
     * @param encoder
     * @return
     */
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    /**
     * 从 TLV Block 中解码出一个 Interest
     *
     * @param block
     * @return
     */
    bool WireDecode(mindev::encoding::Block& block) override ;
    static int GetSliceNumber(const std::vector<char>& buf){
        auto len = BytesToLong(buf);
        return (len-1)/packet_size+1;
    }
private:
    static const int packet_size = 7000;
    static long BytesToLong(const std::vector<char>& buf,bool is_bigend=true){
        long res = 0;
        if(buf.size()<4)return res;
        if (is_bigend) {
            // 大端序系统直接转换
            res = (static_cast<uint64_t>(buf[0]) << 24) |
                   (static_cast<uint64_t>(buf[1]) << 16) |
                   (static_cast<uint64_t>(buf[2]) << 8) |
                   (static_cast<uint64_t>(buf[3]));
        } else {
            // 小端序系统需要反转
            res = (static_cast<uint64_t>(buf[3]) << 24) |
                   (static_cast<uint64_t>(buf[2]) << 16) |
                   (static_cast<uint64_t>(buf[1]) << 8) |
                   (static_cast<uint64_t>(buf[0]));
        }
        return res;
    }
};
}
    
#endif