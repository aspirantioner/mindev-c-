#include "mindev/include/mgmt/logicfacecommands/logicfacelistcommand.h"
#include "mindev/include/mgmt/logicfacecommands/logicfacecommands.h"
namespace mindev::mgmt::logicfacecommands {
LogicFaceListCommand LogicFaceListCommand::CreateLogicFaceListCommand(const std::string &topPrefix) {
    LogicFaceListCommand command;
    command.SetTopPrefix(topPrefix);
    command.SetModuleName(ManagementModuleFaceMgmt);
    command.SetAction(LogicFaceCommands::LogicFaceManagementActionList);
    return command;
}
} // namespace mindev::mgmt::logicfacecommands
