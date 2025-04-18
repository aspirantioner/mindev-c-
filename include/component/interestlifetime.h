
#ifndef INTERESTLIFETIME_H_
#define INTERESTLIFETIME_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class InterestLifeTime:public mindev::encoding::IEncodingAble,public InitialAble,public TlvComponentBase{
private:
    long interestLifeTime;
    };
}

#endif
