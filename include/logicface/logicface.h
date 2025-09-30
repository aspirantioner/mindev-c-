#ifndef LOGICFACE_H_
#define LOGICFACE_H_

#include "./logicfacecounters.h"
#include "./itransport.h"
#include "./linkservice.h"
#include <memory>
#include <sys/types.h>
#include "mindev/include/security/keychain.h"
#include "mindev/include/component/identifier.h"
#include "./iregisterprefixhelper.h"
#include "mindev/include/packet/minpacket.h"
#include "mindev/include/packet/cpacket.h"
#include "mindev/include/encoding/tlv.h"
#include "mindev/include/packet/lppacket.h"
#include "mindev/include/packet/interest.h"
#include "mindev/include/packet/data.h"


namespace mindev::logicface{
    class LinkService;
    enum LogicFaceType{
        TCP = 0,
        UDP = 1,
        Ether = 2,
        Unix = 3,
        Inner = 4,
    };
    const int DefaultMtuSize = 9000;
    // 分片兴趣包发送情况
    static const int PENDING = -3;
    static const int FAIL = -2;
    static const int FINISHED = -1;
    class LogicFace{
public:
    typedef std::shared_ptr<LogicFace> ptr; 
    LogicFaceType type;
    long expire_time;
    bool state;
    LogicFaceCounters logicFaceCounters;
    ITransport::ptr transport;
    LinkService::ptr linkService;
    mindev::security::KeyChain keyChain;// 用于注册前缀时进行签名
    LogicFace(){}
    bool InitWithTcp(const std::string& ip,u_short port);
    bool InitWithUdp(const std::string& ip,u_short port);
    /**
     * GetKeyChain 获取用于注册前缀时签名的秘钥链
     * @return
     */
    mindev::security::KeyChain& GetKeyChain(){return this->keyChain;}
    /**
     * SetKeyChain 设置用于注册前缀时签名的秘钥链
     * @param keyChain
     */
    void SetKeyChain(const mindev::security::KeyChain& keyChain){this->keyChain=keyChain;}
    /**
     * 在MIR中注册一个标识，路由指向本客户端
     * //				（1） 构造一个命令兴趣包， 通过l.SendInterest(interest) 把兴趣包发出去；
     * //				（2） 等待一个数据包， 如果等待超时，则报错，如果接收到的包不是数据包则报错；
     * //				（3） 解析收到的数据包，根据数据包中的应答信息判断标识是否注册成功
     * @param identifier 要添加的路由标识
     * @param timeout 超时时间，以  毫秒  为单位
     * @return
     */
    bool RegisterIdentifier(const mindev::component::Identifier& identifier,long timeout,std::shared_ptr<IRegisterPrefixHelper> helper){return helper->RegisterPrefix(identifier,*this,this->keyChain);}
    /**
     * 从 LogicFace 中接收一个网络包
     * @param timeout 读超时时间， 毫秒为单位， 小于 0 表示不超时
     * @return 多标识网络包
     * @throws LogicFaceException
     */
    inline std::optional<mindev::packet::MINPacket> ReceivePacket(long timeout){
        if(!this->transport->SetReadTimeout(timeout)){
            return std::nullopt;
        }
        return this->linkService->ReceivePacket();
    }
    /**
     * 从 LogicFace 中接收一个普通推送式网络包， 如果收到的包不是普通推送式网络包，则这个包会被忽略
     * @param timeout 读超时时间， 毫秒为单位， 小于 0 表示不超时
     * @return
     * @throws LogicFaceException
     */
    std::optional<mindev::packet::CPacket> ReceiveCPacket(long timeout){
        while(true){
            std::optional<mindev::packet::MINPacket> minPacket=this->ReceivePacket(timeout);
            int packetType= bigint::_bigint_to<int>(minPacket->GetPacketType().value().GetVlIntValue());
            if(packetType==mindev::encoding::TLV::TlvIdentifierCommon){
                std::optional<mindev::packet::CPacket> cPacket=mindev::packet::CPacket().CreateCPacketByMINPacket(minPacket.value());
                return cPacket;
            }
        }
    }
    /**
     * 直接读取LpPacket，减少读包阻塞时间
     * @param timeout
     * @return
     * @throws LogicFaceException
     */
    std::optional<mindev::packet::LpPacket> ReceiveQuickCPacketV3(long timeout){
        if(!this->transport->SetReadTimeout(timeout)){
            return std::nullopt;
        }
        return this->linkService->ReceiveQuickPacket();
    }
    /**
     * 从 LogicFace 中接收一个普通推送式网络包， 如果收到的包不是普通推送式网络包，则这个包会被忽略
     * @param timeout 读超时时间， 毫秒为单位， 小于 0 表示不超时
     * @return
     * @throws LogicFaceException
     */
    std::optional<mindev::packet::Interest> ReceiveInterest(long timeout){
        while(true){
            std::optional<mindev::packet::MINPacket> minPacket=this->ReceivePacket(timeout);
            if(!minPacket.has_value()){
                return std::nullopt;
            }
            int packetType=bigint::_bigint_to<int>(minPacket->GetPacketType().value().GetVlIntValue());
            if(packetType==mindev::encoding::TLV::TlvIdentifierContentInterest){
                std::optional<mindev::packet::Interest> interest=mindev::packet::Interest().CreateInterestByMINPacket(minPacket.value());
                return interest;
            }
        }
    }
    /**
     * 从 LogicFace 中接收一个数据包， 如果收到的包不是数据包，则这个包会被忽略
     * @param timeout 读超时时间， 毫秒为单位， 小于 0 表示不超时
     * @return
     */
    std::optional<mindev::packet::Data> ReceiveData(long timeout){
        while(true){
            std::optional<mindev::packet::MINPacket> minPacket=this->ReceivePacket(timeout);
            if(!minPacket.has_value()){
                return std::nullopt;
            }
            int packetType=bigint::_bigint_to<int>(minPacket->GetPacketType().value().GetVlIntValue());
            if(packetType==mindev::encoding::TLV::TlvIdentifierContentData){
                std::optional<mindev::packet::Data> data =mindev::packet::Data().CreateDataByMINPacket(minPacket.value());
                return data;
            }
        }
    }
    /**
     * 发送一个MIN包
     * @param minPacket
     * @return
     */
    bool SendPacket(const mindev::packet::MINPacket& minPacket){return this->linkService->SendMINPacket(minPacket);}
    /**
     * 发送一个普通推送式网络包
     * @param cPacket
     * @return
     */
    bool SendCPacket(const mindev::packet::CPacket& cPacket){return this->linkService->SendCPacket(cPacket);}
    /**
     * 快发包：减少分包过程，迅速将包发送出去
     * @param cPacket
     * @return
     * @throws LogicFaceException
     */
    bool SendQuickCPacket(const mindev::packet::CPacket& cPacket){return this->linkService->SendQuickCPacket(cPacket);}
    /**
     * 快发包V3：减少TLV编码及分包过程
     * @param encodedBytes
     * @return
     * @throws LogicFaceException
     */
    bool SendQuickCPacketV3(const std::vector<char>& encodedBytes){return this->linkService->SendQuickCPacketV3(encodedBytes);}
    /**
     * 发送一个兴趣包
     * @param interest
     * @return
     * @throws LogicFaceException
     */
    bool SendInterest(const mindev::packet::Interest& interest){return this->linkService->SendInterest(interest);}
    /**
     * 发送一个数据包
     * @return
     */
    bool SendData(const mindev::packet::Data& data){return this->linkService->SendData(data);}
    inline bool ShutDown(){
        if(this->state){
           this->transport->Close();
           this->state=false;
//            this.executorService.shutdown();
//            this.ITransport.close();
        }
        return true;
    }
    /**
     * 获得本地地址
     * @return
     */
    std::string GetLocalUri(){return this->transport->GetLocalUri();}
    /**
     * 获得对端地址
     * @return
     */
    std::string GetRemoteUri(){return this->transport->GetRemoteUri();}
    };
}

#endif