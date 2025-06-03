#ifndef MUSTBEREFRESH_H_
#define MUSTBEREFRESH_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
namespace mindev::component{
    class MustBeRefresh:public mindev::encoding::IEncodingAble,public InitialAble,public TlvComponentBase{
private:
    bool mustBeRefresh;
public:
    MustBeRefresh(){}
    MustBeRefresh(bool mustBeRefresh){
        this->SetMustBeRefresh(mustBeRefresh);
    }
    inline bool GetMustBeRefresh(){return this->mustBeRefresh;}
    inline void SetMustBeRefresh(bool mustBeRefresh){
        this->mustBeRefresh = mustBeRefresh;
        this->doInitial();
    }
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
