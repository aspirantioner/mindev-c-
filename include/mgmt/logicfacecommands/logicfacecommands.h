#ifndef LOGICFACECOMMANDS_H_
#define LOGICFACECOMMANDS_H_
#include <string>
namespace mindev::mgmt::logicfacecommands{
class LogicFaceCommands{
public:
    inline static const std::string LogicFaceManagementActionList = "list";
    inline static const std::string LogicFaceManagementActionAdd  = "add";
    inline static const std::string LogicFaceManagementActionDel  = "del";
};
}
#endif
