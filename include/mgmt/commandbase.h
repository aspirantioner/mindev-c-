#ifndef COMMANDBASE_H_
#define COMMANDBASE_H_

#include "mindev/include/mgmt/icontrolcommand.h"

namespace mindev::mgmt {
    class CommandBase:public IControlCommnd{
        inline static const std::string ManagementModuleFaceMgmt = "face-mgmt";
        inline static const std::string ManagementModuleFibMgmt = "fib-mgmt";
        inline static const std::string ManagementModuleCsMgmt = "cs-mgmt";
public:
    std::string topPrefix;
    std::string moduleName;
    std::string action;
    ControlParameters parameters;
    };
}

#endif