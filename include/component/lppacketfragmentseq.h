
#ifndef LPPACKETFRAGMENTSEQ_H_
#define LPPACKETFRAGMENTSEQ_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class LpPacketFragmentSeq:public mindev::encoding::IEncodingAble,public InitialAble,public TlvComponentBase{
public:
    typedef std::shared_ptr<LpPacketFragmentSeq> ptr;
    inline long GetFragmentSeq(){return this->fragmentSeq;}
    inline void SetFragmentSeq(long fragmentSeq){this->fragmentSeq = fragmentSeq;this->doInitial();}
    LpPacketFragmentSeq(){}
    LpPacketFragmentSeq(long fragmentSeq){this->SetFragmentSeq(fragmentSeq);}
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    long fragmentSeq;
    };
}

#endif
