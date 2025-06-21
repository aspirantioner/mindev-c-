#include "mindev/include/mgmt/commandbase.h"



namespace mindev::mgmt{
static std::optional<mindev::packet::Interest> CommandBase::CreateCommandIdentifierInterest(const ControlParameters& parameters,const std::string& prefix){
    mindev::packet::Interest interest;
    mindev::component::Identifier commandIdentifier(prefix);
    mindev::encoding::Encoder encoder;
    if(!encoder.EncoderReset(mindev::encoding::SizeT(mindev::encoding::Encoder::MaxPacketSize), mindev::encoding::SizeT(0))){
        return std::nullopt;
    }
    if(const_cast<ControlParameters&>(parameters).WireEncode(encoder)<0){
    return std::nullopt;
    }
    std::vector<char> controlParametersbuf=encoder.GetBuffer();
    commandIdentifier.Append(mindev::component::IdentifierComponent(controlParametersbuf));
    interest.SetName(commandIdentifier);
    return interest;
}
static std::optional<ControlParameters> CommandBase::ParseControlParameters(const mindev::packet::Interest& interest){
    ControlParameters controlParameters;
    mindev::component::Identifier identifier=const_cast<mindev::packet::Interest&>(interest).GetName();
    mindev::component::IdentifierComponentContainer components=identifier.GetComponents();
    int length=components.Length();
    if(length<3){
        return std::nullopt;
    }
    //没有分片 最后一个就是控制参数
    if(components.GetElement(length-1).IsByteArray()){
        mindev::encoding::Block block(components.GetElement(length-1).GetByteArray(),true);
        if(!controlParameters.WireDecode(block)){
            return std::nullopt;
        }
    }else if(components.GetElement(length-1).IsFragmentNumber()&&components.GetElement(length-2).IsVersionNumber()&&components.GetElement(length-3).IsByteArray()){
            //如果最后一位是分片号 倒数第二位是版本号 倒数第三位是控制参数
            //解析倒数第三位的控制参数
            mindev::encoding::Block block(components.GetElement(length-3).GetByteArray(),true);
            if(!controlParameters.WireDecode(block)){
                return std::nullopt;
            }
        }else{
            //否则没有对应参数报错
            return std::nullopt;
        }
    return controlParameters;
    }
}