#ifndef CONTROLPARAMETERLOCALURI_H_
#define CONTROLPARAMETERLOCALURI_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
#include <string>

namespace mindev::component{
    class ControlParameterLocalUri:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
private:
    std::string localUri;
public:
    typedef std::shared_ptr<ControlParameterLocalUri> ptr;
    ControlParameterLocalUri(){};
    ControlParameterLocalUri(const std::string& localUri){this->SetLocalUri(localUri);};
    inline void SetLocalUri(const std::string& localUri){this->localUri = localUri;this->doInitial();};
    inline std::string GetLocalUri(){return this->localUri;};
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
