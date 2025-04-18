#ifndef CONTROLPARAMETERURI_H_
#define CONTROLPARAMETERURI_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
#include <string>

namespace mindev::component{
    class ControlParameterUri:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    std::string uri;
public:
    typedef std::shared_ptr<ControlParameterUri> ptr;
    };
}

#endif
