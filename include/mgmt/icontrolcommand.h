#ifndef ICONTROLCOMMAND_H_
#define ICONTROLCOMMAND_H_

#include <string>
namespace mindev::mgmt{
    class IControlCommnd{
public:
    virtual std::string GetTopPrefix()=0;
    virtual std::string GetModuleName()=0;
    virtual std::string GetAction()=0;
    
    };
}

#endif
