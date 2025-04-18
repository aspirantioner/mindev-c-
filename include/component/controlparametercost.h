
#ifndef CONTROLPARAMETERCOST_H_
#define CONTROLPARAMETERCOST_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class ControlParameterCost:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long cost;
public:
    typedef std::shared_ptr<ControlParameterCost> ptr;
    };
}

#endif
