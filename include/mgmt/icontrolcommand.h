#ifndef ICONTROLCOMMAND_H_
#define ICONTROLCOMMAND_H_

#include <string>
#include "mindev/include/mgmt/controlparameters.h"

namespace mindev::mgmt{
    class IControlCommand{
public:
    virtual std::string& GetTopPrefix()=0;
    virtual std::string& GetModuleName()=0;
    virtual std::string& GetAction()=0;
    virtual ControlParameters& getParameters()=0;
    };
}

#endif
