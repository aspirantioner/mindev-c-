#ifndef CONTROLPARAMETERPREFIX_H_
#define CONTROLPARAMETERPREFIX_H_

#include "mindev/include/component/identifier.h"
#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"

namespace mindev::component{
    class ControlParameterPrefix:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    Identifier prefix;
public:
    typedef std::shared_ptr<ControlParameterPrefix> ptr;
    };
}

#endif
