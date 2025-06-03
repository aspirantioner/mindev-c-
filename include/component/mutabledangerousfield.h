#ifndef MUTABLEDANGEROUSFIELD_H_
#define MUTABLEDANGEROUSFIELD_H_

#include "mindev/include/component/mutableattrfield.h"
#include "tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
#include "mindev/include/encoding/elementcontainer.h"

namespace mindev::component{
    class MutableDangerousField:public TlvComponentBase,public mindev::encoding::IEncodingAble,public MutableAttrField{
public:
    typedef std::shared_ptr<MutableDangerousField> ptr;
    MutableDangerousField(){}
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
