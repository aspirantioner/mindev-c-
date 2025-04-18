#ifndef LINKSERVICE_H_
#define LINKSERVICE_H_

#include "./itransport.h"
#include <memory>
#include <vector>

class LogicFace;
namespace mindev::logicface{
    const int LpPacketHeaderMaxSize = 1000;
    class LinkService{
public:
    typedef std::shared_ptr<LinkService> ptr; 
    ITransport iTransport;
    std::shared_ptr<LogicFace> logicFace;
    int mtu;
    int lpPacketHeadSize;
    long lpPacketId;
    std::vector<char> cpacketBytes;
    void init(int mtu);
    void calculateLpPacketHeadSize();
    };
    
}
#endif