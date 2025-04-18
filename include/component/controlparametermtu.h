
#ifndef CONTROLPARAMETERMTU_H_
#define CONTROLPARAMETERMTU_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class ControlParameterMtu:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long mtu;
public:
    typedef std::shared_ptr<ControlParameterMtu> ptr;
    };
}

#endif
