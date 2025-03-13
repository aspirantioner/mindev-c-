#ifndef SCOKET_CHANNEL_H_
#define SCOKET_CHANNEL_H_

#include <bits/alltypes.h>
#include <cassert>
#include <cerrno>
#include <memory>
#include "mindev/include/vmsconnection/tcpnet/net_address.h"
#include "mindev/include/common/log.h"
using namespace std;

namespace mindev::vmsconnection::tcpnet{
    class SocketChannel {
        public:
            typedef std::shared_ptr<SocketChannel> ptr; 
            SocketChannel(NetAddress::ptr net_address):m_romote_addr(net_address){}
            ~SocketChannel(){
                Close();
            }
            bool Connect();
            inline void Close(){
                OH_LOG_INFO(LOG_APP,"conn %{public}s closed!",m_romote_addr->ToString().c_str());
                close(m_fd);
            }
            inline int Read(std::vector<uint8_t>& read_buffer){
                static struct timeval timeout{.tv_sec=2,.tv_usec=0};
                static int read_error_count = 3;
                int read_count = 0;
                ssize_t len = 0;
                while(read_count<read_error_count){
                    if (setsockopt(m_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
                        perror("setsockopt error");
                        exit(1);
                    }
                    len = read(m_fd,read_buffer.data(),read_buffer.size());
                    read_count++;
                    if (len==-1 && (errno == EAGAIN || errno == EWOULDBLOCK)){
                        continue;
                    }
                    break;
                }
                OH_LOG_INFO(LOG_APP,"buffer len is %{public}d ,read len is %{public}d",int(read_buffer.size()),len);
                return len;
            }
            inline int Read(std::vector<uint8_t>& read_buffer,int need_read_len){
                assert(read_buffer.size()>=need_read_len);
                return read(m_fd,read_buffer.data(),need_read_len);
            }
            inline int Write(std::vector<uint8_t>& write_buffer){
                auto len = write(m_fd,write_buffer.data(),write_buffer.size());
                OH_LOG_INFO(LOG_APP,"buffer len is %{public}d ,write len is %{public}d",int(write_buffer.size()),len);
                return len;
            }
            inline int Write(std::vector<uint8_t>& write_buffer,int write_len){
                assert(write_len<=write_buffer.size());
                return write(m_fd,write_buffer.data(),write_len);
            }
            inline bool GetState(){return m_state;}
        private:
            NetAddress::ptr  m_romote_addr;
            int m_fd;
            bool m_state=false;
    };
}

#endif
