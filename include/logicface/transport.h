#ifndef TRANSPORT_H_
#define TRANSPORT_H_

#include "./linkservice.h"
#include "mindev/include/packet/lppacket.h"

#include <string>
namespace mindev::logicface {
    class Transport{
public:
    std::string localAddr;
    std::string remoteAddr;
    std::string localUri;
    std::string remoteUri;
    std::weak_ptr<LinkService> linkService;
    std::optional<mindev::packet::LpPacket> ParseByteArrayToLpPacket(std::vector<char>& buf);
    std::vector<char> EncodeLpPacketToByteArray(mindev::packet::LpPacket& lpPacket);
    
    inline std::string& GetRemoteUri(){
        return this->remoteUri;
    }
    
    inline std::string& GetLocalUri(){
        return this->localUri;
    }
    
    inline std::string& GetRemoteAddr(){
        return this->remoteAddr;
    }

    inline std::string& GetLocalAddr(){
        return this->localAddr;
    }
    
    };
}


#endif