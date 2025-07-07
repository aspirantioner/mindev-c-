#ifndef STREAMTRANSPORT_H_
#define STREAMTRANSPORT_H_

#include "./transport.h"
#include "./itransport.h"
#include "mindev/include/vmsconnection/tcpnet/socket_channel.h"
#include <vector>

namespace mindev::logicface {
    class StreamTransport: public Transport,public ITransport{
public:
    mindev::vmsconnection::tcpnet::SocketChannel m_scoket_channel;
    std::vector<char> recBuf;
    long recvLen;
    void Close(){this->m_scoket_channel.Close();}
    bool Send(mindev::packet::LpPacket& lpPacket);
    std::optional<mindev::packet::LpPacket> Receive();
    bool SetReadTimeout(long duration);
private:
    std::pair<long,mindev::packet::LpPacket> ReadPktAndDeal(const std::vector<char>& buf,long buflen);
    mindev::packet::LpPacket DoReceive();
    };
}

#endif