#ifndef READONLYFIELD_H_
#define READONLYFIELD_H_

#include "mindev/include/encoding/iencodingable.h"
#include "tlvcomponentbase.h"

namespace mindev::component{
    class ReadOnlyField:public TlvComponentBase,public mindev::encoding::IEncodingAble{
private:
    mindev::encoding::ElementContainer::ptr blocks = std::make_shared<mindev::encoding::ElementContainer>();
    };
}

#endif
