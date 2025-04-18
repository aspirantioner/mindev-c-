
#ifndef CONGESTIONMARK_H_
#define CONGESTIONMARK_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class CongestionMark:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long congestionMark;
    };
}

#endif
