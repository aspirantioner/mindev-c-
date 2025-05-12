#include "mindev/include/component/controlparameteruri.h"

namespace mindev::component{
    int ControlParameterUri::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        std::vector<char> vec(this->uri.begin(),this->uri.end());
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
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementUri));
        if(tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;
        return totalLength;
    }
    bool ControlParameterUri::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementUri))){
            return false;
        };
        this->SetUri(std::string(block.GetValue().begin(),block.GetValue().end()));
        return true;
    }
}
