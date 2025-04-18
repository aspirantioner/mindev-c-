#ifndef LOGICFACE_H_
#define LOGICFACE_H_

#include "./logicface_counters.h"
#include "./itransport.h"
#include <memory>
#include <sys/types.h>


namespace mindev::logicface{
    class LinkService;
    enum LogicFaceType{
        TCP = 0,
        UDP = 1,
        Ether = 2,
        Unix = 3,
        Inner = 4,
    };
    const int DefaultMtuSize = 9000;
    class LogicFace{
public:
    typedef std::shared_ptr<LogicFace> ptr; 
    LogicFaceType type;
    long expire_time;
    bool state;
    LogicFaceCounters::ptr logicFaceCounters;
    ITransport::ptr Transport;
    std::shared_ptr<LinkService> linkService;
    bool initWithTcp(std::string ip,u_short port);
    bool initWithUdp(std::string ip,u_short port);
    };
}

#endif