
#ifndef CONTROLPARAMETERURISCHEME_H_
#define CONTROLPARAMETERURISCHEME_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class ControlParameterUriScheme:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    long uriScheme;
public:
    typedef std::shared_ptr<ControlParameterUriScheme> ptr;
    };
}

#endif
