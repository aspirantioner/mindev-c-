#ifndef FRESHNESSPERIOD_H_
#define FRESHNESSPERIOD_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class FreshnessPeriod:public TlvComponentBase,public mindev::encoding::IEncodingAble,public InitialAble{
private:
    long freshnessPeriod;
public:
    FreshnessPeriod(){};
    FreshnessPeriod(long freshnessperiod){this->SetFreshnessPeriod(freshnessperiod);};
    inline long GetFreshnessPeriod() const{ return this->freshnessPeriod;};
    inline void SetFreshnessPeriod(long freshnessperiod){this->freshnessPeriod = freshnessperiod;this->doInitial();};
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
