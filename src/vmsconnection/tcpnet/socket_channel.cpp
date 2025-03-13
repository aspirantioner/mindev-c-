#include "mindev/include/vmsconnection/tcpnet/socket_channel.h"

namespace mindev::vmsconnection::tcpnet{
    bool SocketChannel::Connect(){
        if(!IPAddress::CheckValidIPAddr(this->m_romote_addr->ToString())){
            OH_LOG_INFO(LOG_APP,"invalid ip addr!");
            return false;
        }
        this->m_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (this->m_fd < 0) {
            OH_LOG_INFO(LOG_APP,"create socket error: %{public}s(errno: %{public}d)\n", strerror(errno),errno);
            return false;
        }
        // 连接到服务器
        auto conn_result = connect(this->m_fd,this->m_romote_addr->GetSockAddr(), this->m_romote_addr->GetSockLen());
        if (conn_result < 0) {
            OH_LOG_INFO(LOG_APP,"Connect failed %d",conn_result);
            close(this->m_fd);
            return false;
        }
        OH_LOG_INFO(LOG_APP,"Connected to server!");
        m_state = true;
        return true;
    }
}