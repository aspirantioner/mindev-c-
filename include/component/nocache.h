#ifndef NOCACHE_H_
#define NOCACHE_H_

#include "tlvcomponentbase.h"
#include "initialable.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class NoCache:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
public:
    NoCache(){}
    NoCache(bool noCache){this->SetNoCache(noCache);}
    inline void SetNoCache(bool noCache){
        this->noCache = noCache;
        this->doInitial();
    }
    inline bool GetNoCache(){return this->noCache;}
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    bool noCache;
    };
}

#endif
