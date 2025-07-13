#ifndef LINKSERVICE_H_
#define LINKSERVICE_H_

#include "./itransport.h"
#include <memory>
#include <vector>


namespace mindev::logicface{
    class LogicFace;
    
    class LinkService{
public:
    typedef std::shared_ptr<LinkService> ptr; 
    std::weak_ptr<ITransport> iTransport;
    std::reference_wrapper<mindev::logicface::LogicFace> logicFace;
    int mtu;
    int lpPacketHeadSize;
    long lpPacketId;
    std::vector<char> cpacketBytes;
    LinkService(std::reference_wrapper<mindev::logicface::LogicFace> val):logicFace(val){}
    bool Init(int mtu);
private:
    bool CalculateLpPacketHeadSize();
    static const int LpPacketHeaderMaxSize = 1000;
    };
    
}
#endif