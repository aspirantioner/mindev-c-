#ifndef IDENTIFIER_H_
#define IDENTIFIER_H_

#include "identifiercomponentcontainer.h"

namespace mindev::component{
    class Identifier{
public:
    typedef std::shared_ptr<Identifier> ptr;
private:
    IdentifierComponentContainer::ptr components = std::make_shared<IdentifierComponentContainer>();
    };
}

#endif
