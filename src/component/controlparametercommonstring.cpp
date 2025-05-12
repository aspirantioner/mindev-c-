#include "mindev/include/component/controlparametercommonstring.h"

namespace mindev::component{
    int ControlParameterCommonString::WireEncode(mindev::encoding::Encoder& encoder){
        this->commonString.SetTlvType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementCommonString));
        return this->commonString.WireEncode(encoder);
    }
    bool ControlParameterCommonString::WireDecode(mindev::encoding::Block& block){
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementCommonString))){
            return false;
        }
        
        return this->commonString.WireDecode(block);
    }
}