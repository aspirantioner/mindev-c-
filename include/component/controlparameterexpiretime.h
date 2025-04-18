
#ifndef CONTROLPARAMETEREXPIRETIME_H_
#define CONTROLPARAMETEREXPIRETIME_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class ControlParameterExpireTime:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long expireTime;
public:
    typedef std::shared_ptr<ControlParameterExpireTime> ptr;
    };
}

#endif
