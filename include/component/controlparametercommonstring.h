#ifndef CONTROLPARAMETERCOMMONSTRING_H_
#define CONTROLPARAMETERCOMMONSTRING_H_

#include "mindev/include/component/commonstring.h"
namespace mindev::component{
    class ControlParameterCommonString:public mindev::encoding::IEncodingAble{
public:
    CommonString commonString;
    typedef std::shared_ptr<ControlParameterCommonString> ptr;
    ControlParameterCommonString(){
        this->commonString.SetTlvType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementCommonString));
    };
    ControlParameterCommonString(const std::string& str){
        this->commonString = CommonString(mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementCommonString),str);
    }
    inline std::string GetCommonString()const{return this->commonString.GetValue();};
    inline void SetCommonString(const std::string& str){this->commonString.SetValue(str);};
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
