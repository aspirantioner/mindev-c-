#ifndef FIBCOMMANDS_H_
#define FIBCOMMANDS_H_
#include <string>
namespace mindev::mgmt::fibcommands {
class FibCommands {
public:
    inline static const std::string FibManagementActionAdd = "add";
    inline static const std::string FibManagementActionDel = "del";
    inline static const std::string FibManagementActionList = "list";
    inline static const std::string FibManagementActionRegister = "register";
};
} // namespace mindev::mgmt::fibcommands

#endif