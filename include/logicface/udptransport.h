#ifndef UDPTRANSPORT_H_
#define UDPTRANSPORT_H_

#include "mindev/include/logicface/itransport.h"
#include "mindev/include/logicface/transport.h"
#include "mindev/include/vmsconnection/tcpnet/socket_channel.h"

namespace mindev::logicface {
    const static int recvBufLen = 9000;
    class UdpTransport :public ITransport,public Transport{
public:
        mindev::vmsconnection::tcpnet::SocketChannel::ptr m_scoket_channel;
        std::vector<char> recBuf;
        long recvLen;
        bool init(mindev::vmsconnection::tcpnet::SocketChannel::ptr channel){
            m_scoket_channel = channel;
            this->recBuf.resize(recvBufLen);
            this->recvLen = 0;
            return true;
        }
    };
}

#endif