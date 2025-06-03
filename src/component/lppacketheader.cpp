#include "mindev/include/component/lppacketheader.h"

namespace mindev::component{
    int LpPacketHeader::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        int tmpLen = this->lpPacketFragmentSeq.WireEncode(encoder);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;

        tmpLen = this->lpPacketFragmentNum.WireEncode(encoder);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;

        tmpLen = this->lpPacketFragmentSeq.WireEncode(encoder);
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;

        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(mindev::encoding::TLV::TlvLpPacketHeader));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        return totalLength;
    }
    bool LpPacketHeader::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvLpPacketHeader))){
            return false;
        }
        if(!block.ParseSubElements()){
            return false;
        }
        auto elementcontainer = block.GetSubElements().GetElements();
        for(auto elem:elementcontainer){
            int type =bigint::_bigint_to<int>(elem.GetType().GetVlIntValue());
            switch(type){
                case mindev::encoding::TLV::TlvLpPacketFragmentId:
                    if(!this->lpPacketFragmentId.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvLpPacketFragmentNum:
                    if(!this->lpPacketFragmentNum.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvLpPacketFragmentSeq:
                    if(!this->lpPacketFragmentSeq.WireDecode(elem)){
                        return false;
                    }
                    break;
            }
        }
        return true;
    }
}
