#ifndef REGISTERPREFIXCOMMAND_H_
#define REGISTERPREFIXCOMMAND_H_
#include "commandbase.h"
#include <string>
#include "mindev/include/mgmt/controlparameters.h"
namespace mindev::mgmt::fibcommands{
class RegisterPrefixCommand:public mindev::mgmt::CommandBase{
public:
    /**
     * CreateRegisterPrefixCommand 创建一个 RegisterPrefixCommand 命令
     * @param topPrefix
     * @param parameters
     * @return
     */
    static RegisterPrefixCommand CreateRegisterPrefixCommand(const std::string& topPrefix,const mindev::mgmt::ControlParameters& parameters);
};

}
#endif