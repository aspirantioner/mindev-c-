#ifndef ICONTROLCOMMAND_H_
#define ICONTROLCOMMAND_H_

#include "identifier.h"
#include <string>

namespace mindev::mgmt{
    class ControlParameters;
    class IControlCommand{
public:
    virtual std::string& GetTopPrefix()=0;
    virtual std::string& GetModuleName()=0;
    virtual std::string& GetAction()=0;
    virtual ControlParameters& getParameters()=0;
    };
}

#endif
