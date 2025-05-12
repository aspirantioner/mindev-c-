#ifndef CONTROLPARAMETERCOST_H_
#define CONTROLPARAMETERCOST_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class ControlParameterCost:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long cost;
public:
    typedef std::shared_ptr<ControlParameterCost> ptr;
    ControlParameterCost(){};
    ControlParameterCost(long cost){this->cost = cost;};
    inline long GetCost()const{return this->cost;};
    inline void SetCost(long cost){this->cost = cost;this->doInitial();};
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
