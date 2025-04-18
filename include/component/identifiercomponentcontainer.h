#ifndef IDENTIFIERCOMPONENTCONTAINER_H_
#define IDENTIFIERCOMPONENTCONTAINER_H_

#include "identifiercomponent.h"

namespace mindev::component{
    class IdentifierComponentContainer{
public:
    typedef std::shared_ptr<IdentifierComponentContainer> ptr;
private:
    std::list<IdentifierComponent> identifierComponents;
    };
}

#endif
