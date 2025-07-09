#include "mindev/include/mgmt/fibcommands/fiblistcommand.h"
#include "mindev/include/mgmt/fibcommands/fibcommands.h"
namespace mindev::mgmt::fibcommands {
FibListCommand FibListCommand::CreateFibListCommand(const std::string &topPrefix) {
    FibListCommand command;
    command.SetTopPrefix(topPrefix);
    command.SetModuleName(ManagementModuleFibMgmt);
    command.SetAction(FibCommands::FibManagementActionList);
    return command;
}
} // namespace mindev::mgmt::fibcommands
