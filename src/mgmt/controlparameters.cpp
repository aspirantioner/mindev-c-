#include "mindev/include/mgmt/controlparameters.h"
#include "mindev/include/component/identifier.h"
#include "mindev_cpp/include/component/identifiercomponentcontainer.h"
#include "mindev_cpp/include/encoding/elementcontainer.h"

namespace mindev::mgmt{
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
            }
        }
        return true;
    }
    bool ControlParameters::Parse(mindev::packet::Interest& interest){
    mindev::component::Identifier identifier=interest.GetName();
    mindev::component::IdentifierComponentContainer components=identifier.GetComponents();
    int len=components.Length();
    if(len<3){
        return false;
    }
    //没有分片 最后一个就是控制参数
    if(components.GetElement(len-1).IsByteArray()){
        mindev::encoding::Block block(components.GetElement(len-1).GetByteArray(),true);
        if(!this->WireDecode(block)){
            return false;
        }
    }else if(components.GetElement(len-1).IsFragmentNumber() && components.GetElement(len-2).IsVersionNumber() && components.GetElement(len-3).IsByteArray()){
    //如果最后一位是分片号 倒数第二位是版本号 倒数第三位是控制参数
    mindev::encoding::Block block(components.GetElement(len-3).GetByteArray(),true);
    if(!this->WireDecode(block)){
        return false;
    }
    }else{
        return false;
    }
    return true;
    }
}