#ifndef MUTABLEFIELD_H_
#define MUTABLEFIELD_H_

#include "mindev/include/component/mutabledangerousfield.h"
#include "tlvcomponentbase.h"
#include "mutableprotectfield.h"
#include "mutablefield.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class MutableField:public TlvComponentBase,public mindev::encoding::IEncodingAble{
public:
    MutableProtectField::ptr mutableProtectField = std::make_shared<MutableProtectField>();
    MutableDangerousProtectField::ptr mutableDangerousFiled = std::make_shared<MutableDangerousProtectField>();
    };
}

#endif
