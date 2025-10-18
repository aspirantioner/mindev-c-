#ifndef PACKETTYPEHELPER_H_
#define PACKETTYPEHELPER_H_

#include "minpacket.h"

namespace mindev::packet{
    class PacketTypeHelper{
public:
    inline static bool IsInterest(const MINPacket& packet){
        //todo:待实现
        return true;
    }
    inline static bool IsData(const MINPacket& packet){
        //todo:待实现
        return true;
    }
    inline static bool IsNack(const MINPacket& packet){
        //todo:待实现
        return true;
    }
    inline static bool IsCPacket(const MINPacket& packet){
        //todo:待实现
        return true;
    }
    
    };
}

#endif
