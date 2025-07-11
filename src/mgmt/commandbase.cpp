#include "mindev/include/mgmt/commandbase.h"

namespace mindev::mgmt{
std::optional<mindev::packet::Interest> CommandBase::CreateCommandIdentifierInterest(const ControlParameters& parameters,const std::string& prefix){
        mindev::packet::Interest interest;
        auto val = mindev::component::Identifier::BuildIdentifierByString(prefix);
        if(!val.has_value()){
            return std::nullopt;
        }
        auto commandIdentifier = val.value();
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
std::optional<ControlParameters> CommandBase::ParseControlParameters(const mindev::packet::Interest& interest){
        ControlParameters controlParameters;
        mindev::component::Identifier identifier=const_cast<mindev::packet::Interest&>(interest).GetName();
        mindev::component::IdentifierComponentContainer components=identifier.GetComponents();
        int length=components.Length();
        if(length<3){
            return std::nullopt;
        }
        //没有分片 最后一个就是控制参数
        if(components.GetIdentifierComponents().back().IsByteArray()){
            auto block = mindev::encoding::Block::CreateBlockByBuffer(components.GetIdentifierComponents().back().GetByteArray(),true);
            if(block.has_value() && !controlParameters.WireDecode(block.value())){
                return std::nullopt;
            }
        }else if(components.GetIdentifierComponents().back().IsFragmentNumber()&&components.GetIdentifierComponents()[-2].IsVersionNumber()&&components.GetIdentifierComponents()[-3].IsByteArray()){
            //如果最后一位是分片号 倒数第二位是版本号 倒数第三位是控制参数
            //解析倒数第三位的控制参数
            auto block = mindev::encoding::Block::CreateBlockByBuffer(components.GetIdentifierComponents()[-3].GetByteArray(),true);
            if(block.has_value() && !controlParameters.WireDecode(block.value())){
                return std::nullopt;
            }
        }else{
            //否则没有对应参数报错
            return std::nullopt;
        }
        return controlParameters;
    }
}