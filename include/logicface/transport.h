#ifndef TRANSPORT_H_
#define TRANSPORT_H_

#include "./linkservice.h"
#include <string>
namespace mindev::logicface {
    class Transport{
public:
    std::string localAddr;
    std::string remoteAddr;
    std::string localUri;
    std::string remoteUri;
    LinkService::ptr linkservice;
    };
}


#endif