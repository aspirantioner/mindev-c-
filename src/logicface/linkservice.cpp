#include "mindev/include/logicface/linkservice.h"

namespace mindev::logicface {
    void LinkService::init(int mtu){
        this->mtu = mtu;
        this->calculateLpPacketHeadSize();
        this->lpPacketId = 0;
        
        return;
    }
    void LinkService::calculateLpPacketHeadSize(){
    
    }
}