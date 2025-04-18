
#ifndef IDENTIFIERWRAPPER_H_
#define IDENTIFIERWRAPPER_H_

#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
#include "mindev/include/component/identifier.h"
#include "mindev/include/encoding/tlv.h"

namespace mindev::component{
    class IdentifierWrapper:public TlvComponentBase,public mindev::encoding::IEncodingAble{
private:
    Identifier::ptr identifier = std::make_shared<Identifier>();
    mindev::encoding::VlInt::ptr tlvType = std::make_shared<mindev::encoding::VlInt>(mindev::encoding::TLV::TlvInvalid);
    };
}

#endif
