#include "mindev/include/logicface/mgmtcommand.h"
#include "mindev/include/component/identifiercomponentcontainer.h"
#include "mindev/include/component/identifiercomponent.h"
#include "mindev/include/mgmt/controlparameters.h"
#include "mindev/include/encoding/encoder.h"
#include "mindev/include/encoding/sizet.h"
#include <optional>
#include <vector>
#include "mindev/include/component/identifiercomponent.h"
namespace mindev::logicface {
std::optional<mindev::packet::Interest>
MgmtCommand::CreateRegisterIdentifierInterest(const mindev::component::Identifier &identifier) {
    // /min-mir/mgmt/localhop/<模块名称>/<命令>/<参数>/[版本号]/[分片号]
    mindev::packet::Interest interest;
    mindev::component::IdentifierComponentContainer componentContainer;
    componentContainer.AddElement(mindev::component::IdentifierComponent(std::string("min-mir")));
    componentContainer.AddElement(mindev::component::IdentifierComponent(std::string("mgmt")));
    componentContainer.AddElement(mindev::component::IdentifierComponent(std::string("localhop")));
    componentContainer.AddElement(mindev::component::IdentifierComponent(std::string("fib-mgmt")));
    componentContainer.AddElement(mindev::component::IdentifierComponent(std::string("add-next-hop")));
    mindev::mgmt::ControlParameters controlParameters;
    controlParameters.controlParameterPrefix.SetPrefix(identifier);
    controlParameters.controlParameterCost.SetCost(25);
    mindev::encoding::Encoder encoder;
    if (!encoder.EncoderReset(mindev::encoding::SizeT(mindev::encoding::Encoder::MaxPacketSize),
                              mindev::encoding::SizeT(0))) {
        return std::nullopt;
    }
    if (controlParameters.WireEncode(encoder) < 0) {
        return std::nullopt;
    }
    std::vector<char> controlParametersbuf = encoder.GetBuffer();
    componentContainer.AddElement(mindev::component::IdentifierComponent(controlParametersbuf));
    auto commandIdentifier = component::Identifier::BuildIdentifierByComponents(componentContainer);
    if(!commandIdentifier.has_value()){
        return std::nullopt;
    }
    interest.SetName(commandIdentifier.value());
    return interest;
}
} // namespace mindev::logicface