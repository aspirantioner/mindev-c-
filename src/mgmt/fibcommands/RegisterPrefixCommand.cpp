#include "mindev/include/mgmt/fibcommands/registerprefixcommand.h"
#include "mindev/include/mgmt/fibcommands/fibcommands.h"
namespace mindev::mgmt::fibcommands {
RegisterPrefixCommand RegisterPrefixCommand::CreateRegisterPrefixCommand(const std::string &topPrefix,
                                                 const mindev::mgmt::ControlParameters &parameters) {
    RegisterPrefixCommand command;
    command.SetTopPrefix(topPrefix);
    command.SetModuleName(ManagementModuleFibMgmt);
    command.SetAction(FibCommands::FibManagementActionRegister);
    command.SetParameters(parameters);
    return command;
}
} // namespace mindev::mgmt::fibcommands
