#include "mindev/include/component/controlparameterpasswd.h"
#include "mindev/include/encoding/selfencodingbase.h"

namespace mindev::component{
    int ControlParameterPasswd::WireEncode(mindev::encoding::Encoder& encoder){
        this->commonString.SetTlvType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementPasswd));
        return this->commonString.WireEncode(encoder);
    }
    bool ControlParameterPasswd::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementPasswd))){
            return false;
        };
        
        return this->commonString.WireDecode(block);
    }
}
