#ifndef HOPLIMIT_H_
#define HOPLIMIT_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class HopLimit:public mindev::encoding::IEncodingAble,public TlvComponentBase,public InitialAble{
private:
    long hopLimit;
public:
    HopLimit(){};
    HopLimit(long hopLimit){this->SetHopLimit(hopLimit);};
    inline long GetHopLimit() const{ return this->hopLimit;};
    inline void SetHopLimit(long hopLimit) {this->hopLimit = hopLimit;this->doInitial();};
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
