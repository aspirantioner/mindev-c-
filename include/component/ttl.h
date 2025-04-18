
#ifndef TTL_H_
#define TTL_H_

#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class TTL:public mindev::encoding::IEncodingAble{
private:
    long ttl;
    };
}

#endif
