
#ifndef LPPACKETFRAGMENTID_H_
#define LPPACKETFRAGMENTID_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class LpPacketFragmentId:public mindev::encoding::IEncodingAble,public InitialAble,public TlvComponentBase{
public:
    typedef std::shared_ptr<LpPacketFragmentId> ptr;
private:
    long id;
    };
}

#endif
