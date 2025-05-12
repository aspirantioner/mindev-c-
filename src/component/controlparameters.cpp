#include "mindev/include/component/controlparameters.h"

namespace mindev::component{
    int ControlParameters::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        int tmpLen = 0;
        
        if(this->controlParameterPrefix.isInitial()){
            tmpLen = this->controlParameterPrefix.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }

        if(this->controlParameterLogicFaceId.isInitial()){
            tmpLen = this->controlParameterLogicFaceId.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }

        if(this->controlParameterCost.isInitial()){
            tmpLen = this->controlParameterCost.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }  
        
        if(this->controlParameterCapacity.isInitial()){
            tmpLen = this->controlParameterCapacity.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }
        
        if(this->controlParameterCount.isInitial()){
            tmpLen = this->controlParameterCount.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }
        
        if(this->controlParameterExpireTime.isInitial()){
            tmpLen = this->controlParameterExpireTime.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }

        if(this->controlParameterUri.isInitial()){
            tmpLen = this->controlParameterUri.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }

        if(this->controlParameterLocalUri.isInitial()){
            tmpLen = this->controlParameterLocalUri.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }
        
        if(this->controlParameterLogicFacePersistency.isInitial()){
            tmpLen = this->controlParameterLogicFacePersistency.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }
        
        if(this->controlParameterUriScheme.isInitial()){
            tmpLen = this->controlParameterUriScheme.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }
        
        if(this->controlParameterMtu.isInitial()){
            tmpLen = this->controlParameterMtu.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }
        
        if(this->controlParameterPasswd.commonString.isInitial()){
            tmpLen = this->controlParameterPasswd.commonString.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }

        if(this->controlParameterCommonString.commonString.isInitial()){
            tmpLen = this->controlParameterCommonString.commonString.WireEncode(encoder);
            if(tmpLen<0){
                return -1;
            }
            totalLength += tmpLen;
        }

        // 编码 TLV-LENGTH
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if (tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        // 编码 TLV-TYPE
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagementControlParameters));
        if (tmpLen<0){
            return -1;
        }
        totalLength+=tmpLen;

        return totalLength;
    }
    bool ControlParameters::WireDecode(mindev::encoding::Block& block){
        if(!block.ParseSubElements()){
            return false;
        }
        
        for(auto elem:block.GetSubElements().GetElements()){
            auto type = bigint::_bigint_to<int>(elem.GetType().GetVlIntValue());
            switch(type){
                case mindev::encoding::TLV::TlvManagementPrefix:
                    if(!this->controlParameterPrefix.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvManagementLogicFaceId:
                    if(!this->controlParameterLogicFaceId.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvManagementCost:
                    if(!this->controlParameterCost.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvManagementCapacity:
                    if(!this->controlParameterCapacity.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvManagementCount:
                    if(!this->controlParameterCount.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvManagementExpireTime:
                    if(!this->controlParameterExpireTime.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvManagementUri:
                    if(!this->controlParameterUri.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvManagementLocalUri:
                    if(!this->controlParameterLocalUri.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvManagementLogicFacePersistency:
                    if(!this->controlParameterLogicFacePersistency.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvManagementUriScheme:
                    if(!this->controlParameterUriScheme.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvManagementMtu:
                    if(!this->controlParameterMtu.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvManagementPasswd:
                    if(!this->controlParameterPasswd.WireDecode(elem)){
                        return false;
                    }
                    break;
                case mindev::encoding::TLV::TlvManagementCommonString:
                    if(!this->controlParameterCommonString.WireDecode(elem)){
                        return false;
                    }
                    break;
            }
        }
        this->doInitial();
        return true;
    }
}
