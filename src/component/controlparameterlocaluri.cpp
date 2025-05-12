#include "mindev/include/component/controlparameterlocaluri.h"

namespace mindev::component{
    int ControlParameterLocalUri::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        std::vector<char> vec(this->localUri.begin(),this->localUri.end());
        int tmpLen = encoder.PrependByteArray(vec,mindev::encoding::SizeT(vec.size()));
        if(tmpLen<0){
            return -1;
        }
        totalLength += tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        tmpLen = encoder.PrependVarNumber(new mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementLocalUri));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool ControlParameterLocalUri::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementLocalUri))){
            return false;
        }
        this->SetLocalUri(std::string(block.GetValue().begin(),block.GetValue().end()));
        return true;
    }
}
