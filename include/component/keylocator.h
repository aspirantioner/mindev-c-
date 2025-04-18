
#ifndef KEYLOCATOR_H_
#define KEYLOCATOR_H_

#include "identifier.h"
#include <memory>

namespace mindev::component{
    class KeyLocator{
public:
    typedef std::shared_ptr<KeyLocator> ptr;
    KeyLocator(){};
private:
    Identifier::ptr identifier = std::make_shared<Identifier>();

    };
}

#endif
