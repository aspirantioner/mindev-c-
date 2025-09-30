#include "mindev/include/mgmt/logicfacecommands/logicfacedelcommand.h"
#include "mindev/include/mgmt/logicfacecommands/logicfacecommands.h"
namespace mindev::mgmt::logicfacecommands {
LogicFaceDelCommand LogicFaceDelCommand::CreateLogicFaceDelCommand(const std::string &topPrefix,
                                                                   long id) {
    LogicFaceDelCommand command;
    command.SetTopPrefix(topPrefix);
    command.SetModuleName(ManagementModuleFaceMgmt);
    command.SetAction(LogicFaceCommands::LogicFaceManagementActionDel);
    mindev::mgmt::ControlParameters parameters;
    parameters.controlParameterLogicFaceId.SetLogicFaceId(id);
    command.SetParameters(parameters);
    return command;
}
} // namespace mindev::mgmt::logicfacecommands
