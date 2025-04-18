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
    ControlParameterPrefix::ptr controlParameterPrefix = std::make_shared<ControlParameterPrefix>();
    ControlParameterLogicFaceId::ptr controlParameterLogicFaceId = std::make_shared<ControlParameterLogicFaceId>();
    ControlParameterCost::ptr controlParameterCost = std::make_shared<ControlParameterCost>();
    ControlParameterCapacity::ptr controlParameterCapacity = std::make_shared<ControlParameterCapacity>();
    ControlParameterCount::ptr controlParameterCount = std::make_shared<ControlParameterCount>();
    ControlParameterExpireTime::ptr controlParameterExpireTime = std::make_shared<ControlParameterExpireTime>();
    ControlParameterUri::ptr controlParameterUri = std::make_shared<ControlParameterUri>();
    ControlParameterLocalUri::ptr controlParameterLocalUri = std::make_shared<ControlParameterLocalUri>();
    ControlParameterLogicFacePersistency::ptr controlParameterLogicFacePersistency = std::make_shared<ControlParameterLogicFacePersistency>();
    ControlParameterUriScheme::ptr controlParameterUriScheme = std::make_shared<ControlParameterUriScheme>();
    ControlParameterMtu::ptr controlParameterMtu = std::make_shared<ControlParameterMtu>();
    ControlParameterPasswd::ptr controlParameterPasswd = std::make_shared<ControlParameterPasswd>();
    ControlParameterCommonString::ptr controlParameterCommonString = std::make_shared<ControlParameterCommonString>();
    };
}

#endif
