#ifndef IENCODINGABLE_H_
#define IENCODINGABLE_H_
#include "encoder.h"
#include "block.h"
namespace mindev::encoding {
    class IEncodingAble{
        virtual int wireEncode(Encoder encoder){return 0;}
        virtual bool wireDecode(Block block){return true;}
    };
}

#endif