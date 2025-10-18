#ifndef MINPACKET_H_
#define MINPACKET_H_

#include "mindev/include/encoding/iencodingable.h"
#include "mindev/include/packet/iminpacket.h"
#include "mindev/include/component/identifierfield.h"
#include "mindev/include/component/signaturefield.h"
#include "mindev/include/component/readonlyfield.h"
#include "mindev/include/component/mutablefield.h"
#include "mindev/include/encoding/vlint.h"

namespace mindev::packet{
class MINPacket :public mindev::encoding::IEncodingAble,public IMINPacket{
    public:
        mindev::component::IdentifierField identifierField;
        mindev::component::SignatureField signatureField;
        mindev::component::ReadOnlyField readOnlyField;
        mindev::component::MutableField mutableField;
        mindev::encoding::VlInt packetType;
        int WireEncode(mindev::encoding::Encoder& encoder) override;
        bool WireDecode(mindev::encoding::Block& block) override;
        bool IsPacketValid() override;
        MINPacket(){this->packetType=mindev::encoding::VlInt(mindev::encoding::TLV::TlvInvalid);};
        std::optional<mindev::encoding::VlInt> GetPacketType();
};
}
#endif
