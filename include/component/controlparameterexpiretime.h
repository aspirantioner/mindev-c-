#ifndef CONTROLPARAMETEREXPIRETIME_H_
#define CONTROLPARAMETEREXPIRETIME_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class ControlParameterExpireTime:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long expireTime;
public:
    typedef std::shared_ptr<ControlParameterExpireTime> ptr;
    ControlParameterExpireTime(){};
    ControlParameterExpireTime(long expireTime){this->SetExpireTime(expireTime);};
    inline void SetExpireTime(long expireTime){this->expireTime = expireTime;this->doInitial();};
    inline long GetExpireTime(){return this->expireTime;};
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
