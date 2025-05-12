#ifndef CONTROLPARAMETERMTU_H_
#define CONTROLPARAMETERMTU_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class ControlParameterMtu:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long mtu;
public:
    typedef std::shared_ptr<ControlParameterMtu> ptr;
    ControlParameterMtu(){};
    ControlParameterMtu(long mtu){this->SetMtu(mtu);};
    inline void SetMtu(long mtu){this->mtu = mtu;this->doInitial();};
    inline long GetMtu(){return this->mtu;};
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
    
}

#endif
