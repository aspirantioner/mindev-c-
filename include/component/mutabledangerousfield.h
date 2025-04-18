
#ifndef MUTABLEDANGEROUSFIELD_H_
#define MUTABLEDANGEROUSFIELD_H_

#include "tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
#include "mindev/include/encoding/elementcontainer.h"

namespace mindev::component{
    class MutableDangerousProtectField:public TlvComponentBase,public mindev::encoding::IEncodingAble{
private:
    mindev::encoding::ElementContainer::ptr blocks = std::make_shared<mindev::encoding::ElementContainer>();    
public:
    typedef std::shared_ptr<MutableDangerousProtectField> ptr;
    };
}

#endif
