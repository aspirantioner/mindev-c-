
#ifndef CONTROLPARAMETERCOUNT_H_
#define CONTROLPARAMETERCOUNT_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class ControlParameterCount:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long count;
public:
    typedef std::shared_ptr<ControlParameterCount> ptr;
    };
}

#endif
