#ifndef FIBADDCOMMAND_H_
#define FIBADDCOMMAND_H_
#include "commandbase.h"
#include <string>
#include "mindev/include/mgmt/controlparameters.h"
namespace mindev::mgmt::fibcommands{
class FibAddCommand:public mindev::mgmt::CommandBase{
public:
        /**
     * CreateFibAddCommand 创建一个 FibAddCommand 命令
     * @param topPrefix
     * @param parameters
     * @return
     */
    static FibAddCommand CreateFibAddCommand(const std::string& topPrefix,const mindev::mgmt::ControlParameters& parameters);
};

}




#endif