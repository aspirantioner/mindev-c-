#ifndef LOGICFACEDELCOMMAND_H_
#define LOGICFACEDELCOMMAND_H_
#include "mindev/include/mgmt/commandbase.h"
namespace mindev::mgmt::logicfacecommands{
class LogicFaceDelCommand:public mindev::mgmt::CommandBase{
public:
    /**
     * CreateLogicFaceDelCommand 创建一个 LogicFaceDelCommand 命令
     * @param topPrefix
     * @param id
     * @return
     */
    static LogicFaceDelCommand CreateLogicFaceDelCommand(const std::string& topPrefix,long id);
};
}

#endif