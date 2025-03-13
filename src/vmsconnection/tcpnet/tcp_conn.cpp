#include "mindev/include/vmsconnection/tcpnet/tcp_conn.h"
#include "mindev/include/vmsconnection/code/bc_coder.h"

namespace mindev::vmsconnection::tcpnet {
    //TcpConn::ptr gTcpConn;
    TcpConn::TcpConn(std::string ip,uint16_t port){
        if(this->m_sokcet_channel.get()!=nullptr){
            this->m_sokcet_channel.reset();
        }
        this->m_sokcet_channel = std::make_shared<SocketChannel>(std::make_shared<IPAddress>(ip,port));
        if(this->m_sokcet_channel->Connect()){
            return;
        }
    }
}