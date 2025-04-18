
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
    };
}

#endif
