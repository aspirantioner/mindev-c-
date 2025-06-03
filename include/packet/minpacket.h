#ifndef MINPACKET_H
#define MINPACKET_H
#include "mindev/include/encoding/Iencodingable.h"
#include "mindev/include/packet/iminpacket.h"
#include "mindev/include/component/identifierfield.h"
#include "mindev/include/component/signaturefield.h"
#include "mindev/include/component/readonlyfield.h"
#include "mindev/include/component/mutablefield.h"
#include "mindev/include/encoding/vlint.h"
namespace minddev::packet{
class MINPacket :public IEncodingAble,IMINPacket{
    public:
        mindev::component::IdentifierField identifierField;
        mindev::component::SignatureField signatureField;
        mindev::component::ReadOnlyField readOnlyField;
        mindev::component::MutableField mutableField;
        mindev::encoding::VlInt packetType;
        int WireEncode(mindev::encoding::Encoder& encoder) override;
        bool WireDecode(mindev::encoding::Block& block) override;
        bool IsPacketValid() override;
        MINPacket();
};
}
#endif
