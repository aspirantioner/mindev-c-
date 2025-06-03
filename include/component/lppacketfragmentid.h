#ifndef LPPACKETFRAGMENTID_H_
#define LPPACKETFRAGMENTID_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class LpPacketFragmentId:public mindev::encoding::IEncodingAble,public InitialAble,public TlvComponentBase{
public:
    typedef std::shared_ptr<LpPacketFragmentId> ptr;
    inline long GetId(){return this->id;}
    inline void SetId(long id){this->id = id;this->doInitial();}
    LpPacketFragmentId(){}
    LpPacketFragmentId(long id){this->SetId(id);}
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    long id;
    };
}

#endif
