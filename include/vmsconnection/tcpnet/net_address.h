#ifndef NET_ADDRESS_H_
#define NET_ADDRESS_H_


#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <unistd.h>

#include <memory>
#include <string>
#include <sstream>
using namespace std;

#define DebugLog std::cout
#define ErrorLog DebugLog

namespace mindev::vmsconnection::tcpnet {


    class NetAddress {
    
         public:
        
              typedef std::shared_ptr<NetAddress> ptr;
              
              virtual sockaddr* GetSockAddr() = 0;
                
              virtual int GetFamily() const = 0;
            
              virtual std::string ToString() const = 0;
            
              virtual socklen_t GetSockLen() const = 0;
    
    };


    class IPAddress : public NetAddress {
    
         public:
              IPAddress(const std::string& ip, uint16_t port);
            
              IPAddress(const std::string& addr);
            
              IPAddress(uint16_t port);
            
              IPAddress(sockaddr_in addr);
            
              sockaddr* GetSockAddr();
            
              int GetFamily() const;
            
              socklen_t GetSockLen() const;
            
              std::string ToString() const;
            
              std::string GetIP() const {
                return m_ip;
              }
            
              int GetPort() const {
                return m_port;
              }
        
         public:
              static bool CheckValidIPAddr(const std::string& addr);
        
        
         private:
          
              std::string m_ip;
              uint16_t m_port;
              sockaddr_in m_addr;
    
    };



}


#endif
