#ifndef ONREGISTERFAILINTERFACE_H_
#define ONREGISTERFAILINTERFACE_H_
#include "mindev/include/component/identifier.h"
namespace mindev::logicface::callbackinterface{
class OnRegisterFailInterface{
public:
    virtual void OnRegisterFail(const mindev::component::Identifier& identifier)=0;
};
}
#endif