#include "mindev/include/mgmt/registerprefixhelper.h"
#include "mindev/include/mgmt/mircontroller.h"
#include "mindev/include/mgmt/concretelogicfacebuilder.h"
#include "mindev/include/mgmt/controlparameters.h"
#include "mindev/include/mgmt/commandexecutor.h"
#include "mindev/include/mgmt/fibcommands/registerprefixcommand.h"
#include "mindev/include/mgmt/controlresponse.h"
#include "mindev/include/mgmt/icontrolcommand.h"
#include <iostream>
#include <optional>
#include <memory>

namespace mindev::mgmt {
bool RegisterPrefixHelper::RegisterPrefix(const mindev::component::Identifier &identifier,
                                          const mindev::logicface::LogicFace &face,
                                          const mindev::security::KeyChain &keyChain) {
    ConcreteLogicFaceBuilder concreteLogicFace(face);
    std::shared_ptr<LogicFaceBuilderInterface> logicFace =
        std::make_shared<ConcreteLogicFaceBuilder>(concreteLogicFace);
    std::optional<MIRController> controller = MIRController::CreateMIRController(logicFace, false, keyChain);
    ControlParameters parameters;
    parameters.controlParameterPrefix.SetPrefix(identifier);
    std::optional<mindev::mgmt::RegisterPrefixCommand> registerPrefixCommand =
        mindev::mgmt::fibcommands::RegisterPrefixCommand::CreateRegisterPrefixCommand("/min-mir/mgmt/localhost", parameters);
    std::shared_ptr<IControlCommand> command = std::make_shared<RegisterPrefixCommand>(registerPrefixCommand.value());
    CommandExecutor commandExecutor = controller.value().PrepareCommandExecutor(command).value();
    if (!commandExecutor.has_value()) {
        return false;
    }
    std::optional<ControlResponse> response = commandExecutor.value().Start();
    if (!response.has_value()) {
        return false;
    }
    // 测试
    std::cout << response.value().type << std::endl;
    std::cout << response.value().msg << std::endl;
    std::cout << response.value().code << std::endl;
    std::cout << response.value().data << std::endl;
    if (response.value().code == ControlResponse::ControlResponseCodeSuccess) {
        return true;
    }
    return false;
}


} // namespace mindev::mgmt