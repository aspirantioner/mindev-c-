#ifndef TCPTRANSPORT_H_
#define TCPTRANSPORT_H_

#include "./streamtransport.h"

namespace mindev::logicface {
    class TcpTransport : public StreamTransport{
public:
    const static long recvBufLen = 1024*1028*4;
    bool Init(mindev::vmsconnection::tcpnet::SocketChannel::ptr channel){
        m_scoket_channel = channel;
        this->recBuf.resize(recvBufLen);
        this->recvLen = 0;
        return true;
    }
    };
}
#endif
