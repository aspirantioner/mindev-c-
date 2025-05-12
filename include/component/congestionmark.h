#ifndef CONGESTIONMARK_H_
#define CONGESTIONMARK_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class CongestionMark:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long congestionMark;
public:
    CongestionMark(){};
    CongestionMark(long congestionMark){this->congestionMark = congestionMark;};
    inline void SetCongestionLevel(long congestionMark){this->congestionMark = congestionMark;this->doInitial();};
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
