#ifndef LOGICFACELISTCOMMAND_H_
#define LOGICFACELISTCOMMAND_H_
#include "mindev/include/mgmt/commandbase.h"
namespace mindev::mgmt::logicfacecommands{
class LogicFaceListCommand:public mindev::mgmt::CommandBase{
public:
    /**
     * CreateLogicFaceListCommand 创建一个 LogicFaceListCommand 命令
     * @param topPrefix
     * @return
     */
    static LogicFaceListCommand CreateLogicFaceListCommand(const std::string& topPrefix);
};
}

#endif