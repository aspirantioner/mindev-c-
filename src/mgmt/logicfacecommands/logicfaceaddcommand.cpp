#include "mindev/include/mgmt/logicfacecommands/logicfaceaddcommand.h"
#include "mindev/include/mgmt/logicfacecommands/logicfacecommands.h"
namespace mindev::mgmt::logicfacecommands {
LogicFaceAddCommand LogicFaceAddCommand::CreateLogicFaceAddCommand(const std::string &topPrefix,
                                                                   const mindev::mgmt::ControlParameters &parameters) {
    LogicFaceAddCommand command;
    command.SetTopPrefix(topPrefix);
    command.SetModuleName(ManagementModuleFaceMgmt);
    command.SetAction(LogicFaceCommands::LogicFaceManagementActionAdd);
    command.SetParameters(parameters);
    return command;
}
} // namespace mindev::mgmt::logicfacecommands
