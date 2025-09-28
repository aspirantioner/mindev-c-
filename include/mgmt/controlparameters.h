#ifndef MGMT_CONTROLPARAMETERS_H_
#define MGMT_CONTROLPARAMETERS_H_

#include "mindev/include/component/controlparameterprefix.h"
#include "mindev/include/component/controlparameterlogicfaceid.h"
#include "mindev/include/component/controlparametercost.h"
#include "mindev/include/component/controlparametercapacity.h"
#include "mindev/include/component/controlparametercount.h"
#include "mindev/include/component/controlparameterexpiretime.h"
#include "mindev/include/component/controlparameteruri.h"
#include "mindev/include/component/controlparameterlocaluri.h"
#include "mindev/include/component/controlparameterlogicfacepersistency.h"
#include "mindev/include/component/controlparameterurischeme.h"
#include "mindev/include/component/controlparametermtu.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::packet {
    class Interest;
}
namespace mindev::mgmt{
    class ControlParameters:public mindev::encoding::IEncodingAble{
public:
    mindev::component::ControlParameterPrefix controlParameterPrefix;
    mindev::component::ControlParameterLogicFaceId controlParameterLogicFaceId;
    mindev::component::ControlParameterCost controlParameterCost;
    mindev::component::ControlParameterCapacity controlParameterCapacity;
    mindev::component::ControlParameterCount controlParameterCount;
    mindev::component::ControlParameterExpireTime controlParameterExpireTime;
    mindev::component::ControlParameterUri controlParameterUri;
    mindev::component::ControlParameterLocalUri controlParameterLocalUri;
    mindev::component::ControlParameterLogicFacePersistency controlParameterLogicFacePersistency;
    mindev::component::ControlParameterUriScheme controlParameterUriScheme;
    mindev::component::ControlParameterMtu controlParameterMtu;
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    bool Parse(mindev::packet::Interest& interest);
    };
}

#endif