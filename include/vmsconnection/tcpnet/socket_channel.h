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
            template<typename T,typename = typename std::enable_if<std::is_integral<T>::value>::type>
            inline int Read(std::vector<T>& read_buffer,int offset = 0){
                assert(read_buffer.size()>offset);
                ssize_t len = 0;
                len = read(m_fd,read_buffer.data()+offset,read_buffer.size()-offset);
                if(len == 0){
                    OH_LOG_INFO(LOG_APP,"peer socket closed!");
                }
                else if (len==-1){
                    if(errno == EAGAIN ){
                        OH_LOG_INFO(LOG_APP,"socket read timeout!");
                    }else{
                        OH_LOG_INFO(LOG_APP,"socket read occur error!");
                    }
                }
                OH_LOG_INFO(LOG_APP,"buffer len is %{public}d ,read len is %{public}d",int(read_buffer.size()),len);
                return len;
            }
//             template<typename T,typename = typename std::enable_if<std::is_integral<T>::value>::type>
//             inline int Read(std::vector<T>& read_buffer,int need_read_len){
//                 assert(read_buffer.size()>=need_read_len);
//                 return read(m_fd,read_buffer.data(),need_read_len);
//             }
            template<typename T,typename = typename std::enable_if<std::is_integral<T>::value>::type>
            inline int Write(std::vector<T>& write_buffer){
                auto len = write(m_fd,write_buffer.data(),write_buffer.size());
                OH_LOG_INFO(LOG_APP,"buffer len is %{public}d ,write len is %{public}d",int(write_buffer.size()),len);
                return len;
            }
            template<typename T,typename = typename std::enable_if<std::is_integral<T>::value>::type>
            inline int Write(std::vector<T>& write_buffer,int offset,int write_len){
                assert(offset+write_len<=write_buffer.size());
                auto len = write(m_fd,write_buffer.data()+offset,write_len);
                OH_LOG_INFO(LOG_APP,"buffer len is %{public}d ,write len is %{public}d",int(write_buffer.size()-offset),len);
                return len;
            }
            inline bool GetState(){return m_state;}
            inline int GetFd(){return this->m_fd;}
            void Test(){
                std::vector<char> vec(99,'0');
                auto len = this->Write(vec);
                return;
            }
        private:
            NetAddress::ptr  m_romote_addr;
            int m_fd;
            bool m_state=false;
    };
}

#endif
