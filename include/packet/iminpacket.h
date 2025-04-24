
#ifndef IMINPACKET_H_
#define IMINPACKET_H_

namespace mindev::packet{
    class IMINPacket{
public:
    virtual bool isPacketValid()=0;
    };
}

#endif
