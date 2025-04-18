
#ifndef MUSTBEREFRESH_H_
#define MUSTBEREFRESH_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class MustBeRefresh:public mindev::encoding::IEncodingAble,public InitialAble,public TlvComponentBase{
private:
    bool mustBeRefresh;
    };
}

#endif
