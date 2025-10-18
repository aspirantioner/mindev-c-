#ifndef FIBLISTCOMMAND_H_
#define FIBLISTCOMMAND_H_
#include "mindev/include/mgmt/commandbase.h"
#include <string>
namespace mindev::mgmt::fibcommands{
class FibListCommand:public mindev::mgmt::CommandBase{
public:
    /**
     * CreateFibListCommand 创建一个 FibListCommand 命令
     * @param topPrefix
     * @return
     */
    static FibListCommand CreateFibListCommand(const std::string& topPrefix);
};

}
#endif