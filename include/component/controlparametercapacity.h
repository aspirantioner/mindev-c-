
#ifndef CONTROLPARAMETERCAPACITY_H_
#define CONTROLPARAMETERCAPACITY_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class ControlParameterCapacity:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long capacity;
public:
    typedef std::shared_ptr<ControlParameterCapacity> ptr;
    };
}

#endif
