
#ifndef LPPACKETHEADER_H_
#define LPPACKETHEADER_H_

#include "mindev/include/component/lppacketfragmentid.h"
#include "mindev/include/component/lppacketfragmentnum.h"
#include "mindev/include/component/lppacketfragmentseq.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class LpPacketHeader:public TlvComponentBase,public mindev::encoding::IEncodingAble{
public:
    LpPacketHeader(){}
    LpPacketHeader(const LpPacketFragmentId& id,const LpPacketFragmentNum& num,const LpPacketFragmentSeq& seq){
        this->lpPacketFragmentId = id;
        this->lpPacketFragmentNum = num;
        this->lpPacketFragmentSeq = seq;
    }
    inline LpPacketFragmentId GetLpPacketFragmentId()const{
        return this->lpPacketFragmentId;
    }
    inline LpPacketFragmentNum GetLpPacketFragmentNum()const{
        return this->lpPacketFragmentNum;
    }
    inline LpPacketFragmentSeq GetLpPacketFragmentSeq()const{
        return this->lpPacketFragmentSeq;
    }
    inline void SetLpPacketFragmentId(const LpPacketFragmentId& id){
        this->lpPacketFragmentId = id;
    }
    inline void SetLpPacketFragmentNum(const LpPacketFragmentNum& num){
        this->lpPacketFragmentNum = num;
    }
    inline void SetLpPacketFragmentSeq(const LpPacketFragmentSeq& seq){
        this->lpPacketFragmentSeq = seq;
    }
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    LpPacketFragmentId lpPacketFragmentId ;
    LpPacketFragmentNum lpPacketFragmentNum ;
    LpPacketFragmentSeq lpPacketFragmentSeq ;
    };
}

#endif
