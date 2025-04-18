
#ifndef CONTROLPARAMETERPASSWD_H_
#define CONTROLPARAMETERPASSWD_H_

#include "mindev/include/encoding/iencodingable.h"
#include "mindev/include/component/commonstring.h"

namespace mindev::component{
    class ControlParameterPasswd:public mindev::encoding::IEncodingAble{
private:
    CommonString::ptr commonString=std::make_shared<CommonString>();
public:
    typedef std::shared_ptr<ControlParameterPasswd> ptr;
    };
}

#endif
