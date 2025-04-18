#ifndef STREAMTRANSPORT_H_
#define STREAMTRANSPORT_H_

#include "./transport.h"
#include "./itransport.h"
#include "mindev/include/vmsconnection/tcpnet/socket_channel.h"
#include <vector>

namespace mindev::logicface {
    class StreamTransport: public Transport,public ITransport{
public:
    mindev::vmsconnection::tcpnet::SocketChannel::ptr m_scoket_channel;
    std::vector<char> recBuf;
    long recvLen;
    };
}

#endif