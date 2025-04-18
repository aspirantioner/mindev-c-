
#ifndef LPPACKETHEADER_H_
#define LPPACKETHEADER_H_

#include "mindev/include/component/lppacketfragmentid.h"
#include "mindev/include/component/lppacketfragmentnum.h"
#include "mindev/include/component/lppacketfragmentseq.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class LpPacketHeader:public TlvComponentBase,public mindev::encoding::IEncodingAble{
private:
    LpPacketFragmentId::ptr lpPacketFragmentId = std::make_shared<LpPacketFragmentId>();
    LpPacketFragmentNum::ptr lpPacketFragmentNum = std::make_shared<LpPacketFragmentNum>();
    LpPacketFragmentSeq::ptr lpPacketFragmentSeq = std::make_shared<LpPacketFragmentSeq>();
    };
}

#endif
