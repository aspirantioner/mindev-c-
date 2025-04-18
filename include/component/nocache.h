#ifndef NOCACHE_H_
#define NOCACHE_H_

#include "tlvcomponentbase.h"
#include "initialable.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class NoCache:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    bool noCache;
    };
}

#endif
