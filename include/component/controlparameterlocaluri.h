#ifndef CONTROLPARAMETERLOCALURI_H_
#define CONTROLPARAMETERLOCALURI_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
#include <string>

namespace mindev::component{
    class ControlParameterLocalUri:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    std::string localUri;
public:
    typedef std::shared_ptr<ControlParameterLocalUri> ptr;
    };
}

#endif
