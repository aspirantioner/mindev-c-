
#ifndef INCOMINGLOGICFACEID_H_
#define INCOMINGLOGICFACEID_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class IncomingLogicFaceId:public mindev::encoding::IEncodingAble,public InitialAble,public TlvComponentBase{
private:
    long incomingLogicFaceId;
    };
}

#endif
