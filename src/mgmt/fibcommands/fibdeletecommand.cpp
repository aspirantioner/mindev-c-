#include "mindev/include/mgmt/fibcommands/fibdeletecommand.h"
#include "mindev/include/mgmt/fibcommands/fibcommands.h"
namespace mindev::mgmt::fibcommands {
FibDeleteCommand FibDeleteCommand::CreateFibDeleteCommand(const std::string &topPrefix,
                                                 const mindev::mgmt::ControlParameters &parameters) {
    FibDeleteCommand command;
    command.SetTopPrefix(topPrefix);
    command.SetModuleName(ManagementModuleFibMgmt);
    command.SetAction(FibCommands::FibManagementActionDel);
    command.SetParameters(parameters);
    return command;
}
} // namespace mindev::mgmt::fibcommands
