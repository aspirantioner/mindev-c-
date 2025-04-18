
#ifndef NONCE_H_
#define NONCE_H_

#include "tlvcomponentbase.h"
#include "initialable.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class Nonce:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long nonce;
    };
}

#endif
