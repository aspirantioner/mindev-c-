#ifndef CONTROLPARAMETERLOGICFACEPERSISTENCY_H_
#define CONTROLPARAMETERLOGICFACEPERSISTENCY_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class ControlParameterLogicFacePersistency:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long persistency;
public:
    typedef std::shared_ptr<ControlParameterLogicFacePersistency> ptr;
    ControlParameterLogicFacePersistency(){};
    ControlParameterLogicFacePersistency(long persistency){this->SetPersistency(persistency);};
    inline void SetPersistency(long persistency){this->persistency = persistency;this->doInitial();};
    inline long GetPersistency(){return this->persistency;};
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
