#ifndef FIBDELETECOMMAND_H_
#define FIBDELETECOMMAND_H_
#include "mindev/include/mgmt/commandbase.h"
#include <string>
#include "mindev/include/mgmt/controlparameters.h"
namespace mindev::mgmt::fibcommands{
class FibDeleteCommand:public mindev::mgmt::CommandBase{
public:
    /**
     * CreateFibDeleteCommand 创建一个 FibDeleteCommand 命令
     * @param topPrefix
     * @param parameters
     * @return
     */
    static FibDeleteCommand CreateFibDeleteCommand(const std::string& topPrefix,const mindev::mgmt::ControlParameters& parameters);
};

}




#endif