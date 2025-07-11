#include "mindev/include/mgmt/fibcommands/fibaddcommand.h"
#include "mindev/include/mgmt/fibcommands/fibcommands.h"
namespace mindev::mgmt::fibcommands {
FibAddCommand FibAddCommand::CreateFibAddCommand(const std::string &topPrefix,
                                                 const mindev::mgmt::ControlParameters &parameters) {
    FibAddCommand command;
    command.SetTopPrefix(topPrefix);
    command.SetModuleName(ManagementModuleFibMgmt);
    command.SetAction(FibCommands::FibManagementActionAdd);
    command.SetParameters(parameters);
    return command;
}
} // namespace mindev::mgmt::fibcommands
