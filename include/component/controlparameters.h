#ifndef CONTROLPARAMETERS_H_
#define CONTROLPARAMETERS_H_

#include "mindev/include/component/controlparametercommonstring.h"
#include "mindev/include/component/controlparametermtu.h"
#include "mindev/include/component/controlparametercapacity.h"
#include "mindev/include/component/controlparametercost.h"
#include "mindev/include/component/controlparametercount.h"
#include "mindev/include/component/controlparameterexpiretime.h"
#include "mindev/include/component/controlparameterlocaluri.h"
#include "mindev/include/component/controlparameterlogicfaceid.h"
#include "mindev/include/component/controlparameterlogicfacepersistency.h"
#include "mindev/include/component/controlparameterpasswd.h"
#include "mindev/include/component/controlparameterprefix.h"
#include "mindev/include/component/controlparameteruri.h"
#include "mindev/include/component/controlparameterurischeme.h"
#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class ControlParameters:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
public:
    ControlParameters(){};
    ControlParameterPrefix controlParameterPrefix = ControlParameterPrefix();
    ControlParameterLogicFaceId controlParameterLogicFaceId = ControlParameterLogicFaceId();
    ControlParameterCost controlParameterCost = ControlParameterCost();
    ControlParameterCapacity controlParameterCapacity = ControlParameterCapacity();
    ControlParameterCount controlParameterCount = ControlParameterCount();
    ControlParameterExpireTime controlParameterExpireTime = ControlParameterExpireTime();
    ControlParameterUri controlParameterUri = ControlParameterUri();
    ControlParameterLocalUri controlParameterLocalUri = ControlParameterLocalUri();
    ControlParameterLogicFacePersistency controlParameterLogicFacePersistency = ControlParameterLogicFacePersistency();
    ControlParameterUriScheme controlParameterUriScheme = ControlParameterUriScheme();
    ControlParameterMtu controlParameterMtu = ControlParameterMtu();
    ControlParameterPasswd controlParameterPasswd = ControlParameterPasswd();
    ControlParameterCommonString controlParameterCommonString = ControlParameterCommonString();
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
