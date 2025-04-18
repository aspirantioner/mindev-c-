
#ifndef LPPACKETFRAGMENTNUM_H_
#define LPPACKETFRAGMENTNUM_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class LpPacketFragmentNum:public mindev::encoding::IEncodingAble,public InitialAble,public TlvComponentBase{
public:
    typedef std::shared_ptr<LpPacketFragmentNum> ptr;
private:
    long fragmentNum;
    };
}

#endif
