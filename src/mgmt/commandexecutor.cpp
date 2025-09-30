#include "mindev/include/mgmt/commandexecutor.h"
#include "mindev/include/mgmt/icontrolcommand.h"
#include "mindev/include/component/identifier.h"
#include "mindev/include/packet/minpacket.h"
#include "mindev/include/packet/packettypehelper.h"
#include "mindev/include/encoding/vlint.h"
#include "mindev/include/encoding/tlv.h"
#include "mindev/include/component/nackheader.h"
#include <iostream>

namespace mindev::mgmt {
std::optional<ControlResponse> CommandExecutor::OnReceiveFirstMetaData(const mindev::packet::Data &data) {
    ControlResponse controlResponse;
    
    if (!controlResponse.UnmarshalJSON(data.payload.GetValue())) {
        return std::nullopt;
    }

    switch (controlResponse.code) {
    case ControlResponse::ControlResponseCodeSuccess:
        // 请求成功 直接返回结果
        return controlResponse;
    case ControlResponse::ControlResponseCodeCommonError:
        // 请求失败，直接返回结果，结果中已经包含错误信息
        return controlResponse;
    case ControlResponse::ControlResponseCodeContinue:
        // 请求到元数据，继续请求所有的分片
        // todo
        std::vector<char> bytesBuilder;
        ControlResponseMeta metaData = controlResponse.GetMeta();
        int length = static_cast<int>(metaData.SliceNum);
        // 逐一串行的请求所有的分片，并整合返回的数据
        for (int i = 0; i < length; i++) {
            auto tempInterest = this->NewCommandInterest();
            mindev::component::Identifier tempIdentifier = tempInterest.GetName();
            tempIdentifier.AppendVersionNumber(metaData.Version);
            tempIdentifier.AppendFragmentNumber(i);
            tempInterest.ttl.SetTtl(this->ttl);
            tempInterest.interestLifeTime.SetInterestLifeTime(this->interestLifeTime);
            // 将兴趣包发出
            if (!this->logicFace.SendInterest(tempInterest)) {
                controlResponse.code = ControlResponse::ControlResponseCodeCommonError;
                controlResponse.msg = "Send Interest failed!";
                return controlResponse;
            }
            // 等待接收分片
            std::optional<mindev::packet::MINPacket> newPacket = this->logicFace.ReceivePacket(this->interestLifeTime);
            if (!newPacket.has_value()) {
                controlResponse.code = ControlResponse::ControlResponseCodeCommonError;
                controlResponse.msg = "Request timeout!";
                return controlResponse;
            } else {
                if (mindev::packet::PacketTypeHelper::IsData(newPacket.value())) {
                    std::vector<char> value =
                        newPacket->readOnlyField
                            .GetBlockByType(mindev::encoding::VlInt(mindev::encoding::TLV::TlvPayload))
                            .value()
                            .get()
                            .GetValue();
                    bytesBuilder.insert(bytesBuilder.end(), value.begin(), value.end());
                } else {
                    // 收到的不是Data包,未预期行为
                    controlResponse.code = ControlResponse::ControlResponseCodeCommonError;
                    controlResponse.msg = "Receive other packet（not Data），Unexpected behavior！";
                    return controlResponse;
                }
            }
        }
        break;
        // 得到返回数据
        controlResponse.code = ControlResponse::ControlResponseCodeSuccess;
        controlResponse.msg = "";
        controlResponse.SetBytes(bytesBuilder);
    }
    return controlResponse;
}
mindev::packet::Interest CommandExecutor::NewCommandInterest() {
    mindev::packet::Interest interest;
    mindev::component::Identifier identifier = mindev::component::Identifier::BuildIdentifierByString(this->BuildPrefix(this->command));
    interest.SetName(identifier);
    interest.ttl.SetTtl(this->ttl);
    interest.interestLifeTime.SetInterestLifeTime(this->interestLifeTime);
    interest.isCommandInterest = true;
    this->keyChain.SignInterest(interest);
    // 测试字段----------------
    std::vector<char> value = interest.minPacket.signatureField.GetSignature(0).GetSigValue().GetValue();
    std::string str1(value.begin(), value.end());
    std::cout << "CommandExecutor-构造的兴趣包的签名字段: " << str1 << std::endl;
    mindev::encoding::Encoder encoder;
    if (!encoder.EncoderReset(mindev::encoding::SizeT(mindev::encoding::Encoder::MaxPacketSize),
                              mindev::encoding::SizeT(0))) {
        std::cout << "fucking test";
    }
    int bufLen = interest.WireEncode(encoder);
    std::vector<char> buf = encoder.GetBuffer();
    std::string str2(buf.begin(), buf.end());
    std::cout << "CommandExecutor-构造的兴趣包的最终形态: " << str2 << std::endl;
    // 测试字段----------------
    return interest;
}
std::optional<ControlResponse> CommandExecutor::Start() {
    // 构造管理命令前缀
    std::optional<mindev::packet::Interest> commandInterest = this->NewCommandInterest();
    if (!commandInterest.has_value()) {
        return std::nullopt;
    }
    // 如果存在管理命令参数，则将其添加到命令兴趣包的名字当中
    if (!this->command->GetParameters().empty()) {
        if (!commandInterest->AppendCommandParameters(this->command->GetParameters())) {
            return std::nullopt;
        }
    }
    ControlResponse controlResponse;
    // 打印输出
    std::vector<char> raw1 = mindev::encoding::SelfEncodingBase().SelfWireEncode(commandInterest)->GetRaw();
    std::string str1(raw1.begin(), raw1.end());
    std::cout << "旧的输出【最最终形态】: " << str1 << std::endl;
    mindev::encoding::Encoder encoder;
    if (!encoder.encoderReset(mindev::encoding::SizeT(mindev::encoding::Encoder::MaxPacketSize),
                              mindev::encoding::SizeT(0))) {
        std::cout << "fucking test";
    }
    int bufLen = commandInterest->WireEncode(encoder);
    std::vector<char> buf = encoder.GetBuffer();
    std::string str2(buf.begin(), buf.end());
    std::cout << "新的输出【最最终形态】: " << str2 << std::endl;
    // 发送第一个命令兴趣包
    if (!this->logicFace.SendInterest(commandInterest.value())) {
        return std::nullopt;
    }
    // 等待兴趣包应答
    std::optional<mindev::packet::MINPacket> minPacket =
        this->logicFace.ReceivePacket(commandInterest->interestLifeTime.GetInterestLifeTime());
    std::vector<char> raw2 = mindev::encoding::SelfEncodingBase().SelfWireEncode(minPacket.value())->GetRaw();
    std::string str3(raw2.begin(), raw2.end());
    std::cout << "收到的注册应答包: " << str3 << std::endl;
    // 判断收到的什么包
    if (!minPacket.has_value()) {
        controlResponse.code = ControlResponse::ControlResponseCodeCommonError;
        controlResponse.msg = "Request timeout!";
        return controlResponse;
    }
    // 根据收到的包的类型分别处理
    if (mindev::packet::PacketTypeHelper::IsData(minPacket.value())) {
        // onData
        std::optional<mindev::packet::Data> data = mindev::packet::Data().CreateDataByMINPacket(minPacket.value());
        if (!data.has_value()) {
            return std::nullopt;
        } else {
            return this->OnReceiveFirstMetaData(data.value());
        }
    } else if (mindev::packet::PacketTypeHelper::IsNack(minPacket.value())) {
        // onNack
        std::optional<mindev::packet::Nack> nack = mindev::packet::Nack().CreateNackByMINPacket(minPacket.value());
        if (!nack.has_value()) {
            return std::nullopt;
        } else {
            // onNack
            controlResponse.code = ControlResponse::ControlResponseCodeCommonError;
            controlResponse.msg = "Request failed, receive nack => " +
                                  mindev::component::NackHeader::GetNackReasonString(nack->GetNackReason());
        }
    } else {
        // 受到其他类型的包直接抛出错误，未预期的行为
        controlResponse.code = ControlResponse::ControlResponseCodeCommonError;
        controlResponse.msg = "Receive one other type packet, Unexpected behavior!";
    }
    // 如果设置了自动shutdown，则执行shutdown
    if (this->autoShutdown) {
        if (!this->Shutdown()) {
            return std::nullopt;
        }
    }
    return controlResponse;
}
} // namespace mindev::mgmt
