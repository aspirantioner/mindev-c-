#ifndef ONREGISTERSUCCESSINTERFACE_H_
#define ONREGISTERSUCCESSINTERFACE_H_
#include "mindev/include/component/identifier.h"
namespace mindev::logicface::callbackinterface{
class OnRegisterSuccessInterface{
public:
    virtual void OnRegisterSuccess(const mindev::component::Identifier& identifier)=0;
};
}
#endif