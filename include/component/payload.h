
#ifndef PAYLOAD_H_
#define PAYLOAD_H_
#include "tlvcomponentbase.h"
#include "initialable.h"
#include "mindev/include/encoding/iencodingable.h"
#include <vector>
namespace mindev::component{
    class Payload:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    std::vector<char> value;
    };
}

#endif
