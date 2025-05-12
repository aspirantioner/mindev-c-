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
    ControlParameterUriScheme(){};
    ControlParameterUriScheme(long urischeme){this->SetUriScheme(urischeme);};
    inline long GetUriScheme() const{ return this->uriScheme;};
    inline void SetUriScheme(long urischeme) {this->uriScheme = urischeme;this->doInitial();};
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
