#ifndef CANBEPREFIX_H_
#define CANBEPREFIX_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class CanBePrefix:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
public:
    CanBePrefix(){};
    CanBePrefix(bool canBePrefix){this->canBePrefix=canBePrefix;this->doInitial();};
    inline bool GetCanBePrefix()const{return this->canBePrefix;};
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    bool canBePrefix;
    };
}

#endif
