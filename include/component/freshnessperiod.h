#ifndef FRESHNESSPERIOD_H_
#define FRESHNESSPERIOD_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class FreshnessPeriod:public TlvComponentBase,public mindev::encoding::IEncodingAble,public InitialAble{
private:
    long freshnessPeriod;
    };
}

#endif
