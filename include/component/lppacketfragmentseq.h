
#ifndef LPPACKETFRAGMENTSEQ_H_
#define LPPACKETFRAGMENTSEQ_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class LpPacketFragmentSeq:public mindev::encoding::IEncodingAble,public InitialAble,public TlvComponentBase{
public:
    typedef std::shared_ptr<LpPacketFragmentSeq> ptr;
private:
    long fragmentSeq;
    };
}

#endif
