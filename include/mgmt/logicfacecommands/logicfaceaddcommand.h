#ifndef LOGICFACEADDCOMMAND_H_
#define LOGICFACEADDCOMMAND_H_
#include "mindev/include/mgmt/commandbase.h"
namespace mindev::mgmt::logicfacecommands{
class LogicFaceAddCommand:public mindev::mgmt::CommandBase{
public:
    /**
     * CreateLogicFaceAddCommand 创建一个 LogicFaceAddCommand 命令
     * @param topPrefix
     * @param parameters
     * @return
     */
    static LogicFaceAddCommand CreateLogicFaceAddCommand(const std::string& topPrefix,const mindev::mgmt::ControlParameters& parameters);
};
}

#endif