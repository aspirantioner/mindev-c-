#ifndef IENCODINGABLE_H_
#define IENCODINGABLE_H_

#include "mindev/include/encoding/encoder.h"
#include "mindev/include/encoding/block.h"

namespace mindev::encoding {
    class IEncodingAble{
public:
        virtual int WireEncode(Encoder& encoder){return 0;}
        virtual bool WireDecode(Block& block){return true;}
        virtual ~IEncodingAble() = default;
    };
}

#endif