#ifndef TCP_CONN_H_
#define TCP_CONN_H_
#include "conn.h"
#include "socket_channel.h"
#include <string>

namespace mindev::vmsconnection::tcpnet{
    
    class TcpConn:public Conn {
        public:
            typedef std::shared_ptr<TcpConn> ptr; 
            static  ptr gTcpConn;
            TcpConn(){};
            TcpConn(std::string ip,uint16_t port);
            std::shared_ptr<SocketChannel> m_sokcet_channel;
            bool is_encrypt;
            std::string m_secretkey;
            int m_role;
    };
}
#endif