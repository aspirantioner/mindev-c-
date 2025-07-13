#ifndef ICONTROLCOMMAND_H_
#define ICONTROLCOMMAND_H_

#include <string>
#include "./controlparameters.h"

namespace mindev::mgmt{
    class IControlCommand{
public:
    virtual std::string& GetTopPrefix(){auto tmp = std::string("");return tmp;};
    virtual std::string& GetModuleName(){auto tmp = std::string("");return tmp;};
    virtual std::string& GetAction(){auto tmp = std::string("");return tmp;};
    virtual ControlParameters& getParameters(){auto tmp = ControlParameters();return tmp;};
    };
}

#endif
