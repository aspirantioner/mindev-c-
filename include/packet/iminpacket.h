#ifndef IMINPACKET_H_
#define IMINPACKET_H_

namespace mindev::packet{
    class IMINPacket{
public:
    virtual bool IsPacketValid()=0;
    };
}

#endif
