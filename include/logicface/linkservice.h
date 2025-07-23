#ifndef LINKSERVICE_H_
#define LINKSERVICE_H_

#include "./itransport.h"
#include <memory>
#include <vector>
#include "mindev/include/packet/minpacket.h"
#include "mindev/include/packet/lppacket.h"
#include "mindev/include/packet/data.h"
#include "mindev/include/packet/interest.h"
#include <iostream>


namespace mindev::logicface {
class LogicFace;

class LinkService {
public:
    typedef std::shared_ptr<LinkService> ptr;
    std::weak_ptr<ITransport> transport;
    std::reference_wrapper<mindev::logicface::LogicFace> logicFace;
    int mtu;
    int lpPacketHeadSize;
    long lpPacketId;
    std::vector<char> cpacketBytes;
    LinkService(){}
    LinkService(std::reference_wrapper<mindev::logicface::LogicFace> val) : logicFace(val) {}
    /**
     * 初始化linkService
     * @param mtu
     */
    bool Init(int mtu);
    /**
     * 收到lpPacket包的处理函数，该函数被相关联的 transport 的 receive 函数调用
     * @return
     */
    std::optional<mindev::packet::MINPacket> ReceivePacket();
    std::optional<mindev::packet::LpPacket> ReceiveQuickPacket();
    /**
     * 发送一个兴趣包
     * @param interest
     * @return
     * @throws LogicFaceException
     */
    bool SendInterest(const mindev::packet::Interest &interest);
    /**
     * 发送一个数据包
     * @param data
     * @return
     */
    bool SendData(const mindev::packet::Data &data);
    /**
     * 发送一个普通推送式网络包
     * @param cPacket
     * @return
     */
    bool SendCPacket(const mindev::packet::CPacket &cPacket);
    /**
     * 快发一个推式包：直接默认要发的cpacket只打包成一个lppacket，快速将它发出去
     * @param cPacket
     * @return
     * @throws LogicFaceException
     */
    bool SendQuickCPacket(const mindev::packet::CPacket &cPacket);
    /**
     * 将已经编码好的CPacket变成LpPacket（不分包），然后快速发出去
     * @param encodedBytes
     * @return
     * @throws LogicFaceException
     */
    bool SendQuickCPacketV3(const std::vector<char>& encodedBytes);
    /**
     * 发送一个MIN网络包
     * @param minPacket
     * @return
     */
    bool SendMINPacket(const mindev::packet::MINPacket &minPacket);
    /**
     * 打印自己的状态，测试使用。
     */
    inline void printSelf() {
        std::cout << "lpPacketHeadSize: " << this->lpPacketHeadSize << std::endl;
        std::cout << "mtu: " << this->mtu << std::endl;
        std::cout << "lpPacketId: " << this->lpPacketId << std::endl;
    }

private:
    bool CalculateLpPacketHeadSize();
    static const int LpPacketHeaderMaxSize = 1000;
    /**
     * 从lpPacket中提取出MINPacket对象
     * @param lpPacket
     * @return
     */
    std::optional<mindev::packet::MINPacket> GetMINPacketFromLpPacket(const mindev::packet::LpPacket &lpPacket);
    /**
     * 发送一个lp包分片
     * @param buf 分片的数据
     * @param bufLen 数据长度
     * @param fragmentId  分片号
     * @param fragmentNum 分片数
     * @param fragmentSeq 第几块分片，从0开始
     * @return
     */
    bool SendFragment(const std::vector<char> &buf, int bufLen, long fragmentId, long fragmentNum, long fragmentSeq);
    /**
     * 发送指定长度的一段数据，如果数据过长，会调用sendFragment发送多个分片
     * @param buf
     * @param bufLen
     * @return
     */
    bool SendByteBuffer(const std::vector<char> &buf, int bufLen);
    std::optional<mindev::packet::LpPacket> GetLpPacketFromQuickCPacket(const std::vector<char> &encodedBytes);
    std::optional<mindev::packet::LpPacket> GetLpPacketFromCPacket(const mindev::packet::CPacket &cPacket);
};
} // namespace mindev::logicface
#endif