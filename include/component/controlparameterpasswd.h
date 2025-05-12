
#ifndef CONTROLPARAMETERPASSWD_H_
#define CONTROLPARAMETERPASSWD_H_

#include "mindev/include/encoding/iencodingable.h"
#include "mindev/include/component/commonstring.h"

namespace mindev::component{
    class ControlParameterPasswd:public mindev::encoding::IEncodingAble{
public:
    CommonString commonString;
    typedef std::shared_ptr<ControlParameterPasswd> ptr;
    ControlParameterPasswd(){};
    ControlParameterPasswd(const std::string& passwd){this->commonString=CommonString(mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementPasswd),passwd);};
    inline std::string GetPasswd()const{return this->commonString.GetValue();};
    inline void SetPasswd(const std::string& passwd){this->commonString.SetValue(passwd);};
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
