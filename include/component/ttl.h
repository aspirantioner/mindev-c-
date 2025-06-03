#ifndef TTL_H_
#define TTL_H_

#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class TTL:public mindev::encoding::IEncodingAble{
public:
    TTL(){this->ttl = 64;}
    inline long GetTtl(){return this->ttl;}
    inline void SetTtl(long ttl){this->ttl = ttl;}
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    long ttl;
    };
}

#endif
