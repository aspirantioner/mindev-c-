#include "mindev/include/component/nocache.h"

namespace mindev::component{
    int NoCache::WireEncode(mindev::encoding::Encoder& encoder){
        if(!this->noCache){
            return 0;
        }

        int totalLength = 0; 
        
        int tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(mindev::encoding::TLV::TlvNoCache));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool NoCache::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(),mindev::encoding::VlInt(mindev::encoding::TLV::TlvNoCache))){
            return false;
        }
        this->SetNoCache(true);
        return true;
    }
}
