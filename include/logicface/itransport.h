#ifndef ITRANSPORT_H_
#define ITRANSPORT_H_

#include "mindev/include/packet/lppacket.h"
#include <string>

namespace mindev::logicface{
    class ITransport{
public:
        typedef std::shared_ptr<ITransport> ptr;
        virtual void Close(){};
        virtual bool Send(mindev::packet::LpPacket& lpPacket){return true;};
        virtual std::optional<mindev::packet::LpPacket> Receive(){return std::nullopt;};
        virtual std::string GetRemoteUri() {return "";};
        virtual std::string GetLocalUri() {return "";};
        virtual std::string GetRemoteAddr() {return "";};
        virtual std::string GetLocalAddr() {return "";};
        virtual bool SetReadTimeout(long duration) {return true;};
    };
}

#endif