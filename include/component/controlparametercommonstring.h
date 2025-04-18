
#ifndef CONTROLPARAMETERCOMMONSTRING_H_
#define CONTROLPARAMETERCOMMONSTRING_H_

#include "mindev/include/component/commonstring.h"
namespace mindev::component{
    class ControlParameterCommonString:public mindev::encoding::IEncodingAble{
public:
    CommonString::ptr commonString=std::make_shared<CommonString>();
    typedef std::shared_ptr<ControlParameterCommonString> ptr;
    };
}

#endif
