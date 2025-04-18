
#ifndef HOPLIMIT_H_
#define HOPLIMIT_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class HopLimit:public mindev::encoding::IEncodingAble,public TlvComponentBase,public InitialAble{
private:
    long hopLimit;
    };
}

#endif
