#ifndef CONTROLPARAMETERLOGICFACEID_H_
#define CONTROLPARAMETERLOGICFACEID_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class ControlParameterLogicFaceId:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long logicFaceId;
public:
    typedef std::shared_ptr<ControlParameterLogicFaceId> ptr;
    ControlParameterLogicFaceId(){};
    ControlParameterLogicFaceId(long logicFaceId){this->SetLogicFaceId(logicFaceId);};
    inline void SetLogicFaceId(long logicFaceId){this->logicFaceId = logicFaceId;this->doInitial();};
    inline long GetLogicFaceId(){return this->logicFaceId;};
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
