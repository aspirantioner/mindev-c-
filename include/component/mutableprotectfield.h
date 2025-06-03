#ifndef MUTABLEPROTECTFIELD_H_
#define MUTABLEPROTECTFIELD_H_

#include "mindev/include/component/mutableattrfield.h"
#include "tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
#include "mindev/include/encoding/elementcontainer.h"

namespace mindev::component{
    class MutableProtectField:public TlvComponentBase,public mindev::encoding::IEncodingAble,public MutableAttrField{
public:
    typedef std::shared_ptr<MutableProtectField> ptr;
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
