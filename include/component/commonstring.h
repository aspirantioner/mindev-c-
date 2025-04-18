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
    mindev::encoding::VlInt::ptr tlvType;
    std::string value;
public:
    typedef std::shared_ptr<CommonString> ptr;
    };
}

#endif
