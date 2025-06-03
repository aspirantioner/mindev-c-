
#ifndef INCOMINGLOGICFACEID_H_
#define INCOMINGLOGICFACEID_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class IncomingLogicFaceId:public mindev::encoding::IEncodingAble,public InitialAble,public TlvComponentBase{
private:
    long incomingLogicFaceId;
public:
    IncomingLogicFaceId(){}
    IncomingLogicFaceId(long incomingLogicFaceId){
        this->SetIncomingLogicFaceId(incomingLogicFaceId);
    }
    inline long GetIncomingLogicFaceId(){
        return this->incomingLogicFaceId;
    }
    inline void SetIncomingLogicFaceId(long incomingLogicFaceId){
        this->incomingLogicFaceId = incomingLogicFaceId;
        this->doInitial();
    }
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
