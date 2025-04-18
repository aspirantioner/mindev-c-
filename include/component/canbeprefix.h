
#ifndef CANBEPREFIX_H_
#define CANBEPREFIX_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class CanBePrefix:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    bool canBePrefix;
    };
}

#endif
