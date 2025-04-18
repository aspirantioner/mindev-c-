#ifndef ELEMENTCONTAINER_H_
#define ELEMENTCONTAINER_H_
#include <list>
#include "block.h"

namespace mindev::encoding{
    class Block;
    class ElementContainer {
public:
    typedef std::shared_ptr<ElementContainer> ptr;
private:
    std::list<Block> element_container;
    };
}
#endif
