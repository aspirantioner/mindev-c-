#include "mindev/include/component/mustberefresh.h"

namespace mindev::component{
    int MustBeRefresh::WireEncode(mindev::encoding::Encoder& encoder){
        
        if(!this->mustBeRefresh){
            return 0;
        }

        int totalLength = 0;
        int tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(mindev::encoding::TLV::TlvMustBeRefresh));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        return totalLength;
    }
    bool MustBeRefresh::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvMustBeRefresh))){
            return false;
        }
        this->mustBeRefresh = true;
        this->doInitial();
        return true;
    }
}
