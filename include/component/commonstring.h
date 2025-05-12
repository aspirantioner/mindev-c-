#ifndef COMMONSTRING_H_
#define COMMONSTRING_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
#include "mindev/include/encoding/vlint.h"
#include <string>

namespace mindev::component{
    class CommonString:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    mindev::encoding::VlInt tlvType;
    std::string value;
public:
    typedef std::shared_ptr<CommonString> ptr;
    CommonString(){};
    CommonString(const mindev::encoding::VlInt& tlvType,const std::string& str){
        this->SetTlvType(tlvType);
        this->SetValue(str);
    }
    inline mindev::encoding::VlInt GetTlvType()const{return this->tlvType;};
    inline std::string GetValue()const{return this->value;};
    inline void SetTlvType(const mindev::encoding::VlInt& tlvType){this->tlvType = tlvType;}
    inline void SetValue(const std::string& value){this->value = value;this->doInitial();}
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
