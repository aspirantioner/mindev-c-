#ifndef ELEMENTCONTAINER_H_
#define ELEMENTCONTAINER_H_
#include <list>
#include "block.h"


namespace mindev::encoding{
    class Block;
    class ElementContainer {
public:
    typedef std::shared_ptr<ElementContainer> ptr;
    inline std::list<Block> GetElements() const {return element_container;}
    inline int Length(){return element_container.size();}
    inline void Clear(){element_container.clear();}
    inline void AddElement(const Block& block){element_container.push_back(block);}
    void RemoveElements(const VlInt& tlvType);
    Block GetFirstBlockByType(VlInt tlvType,bool& state) const;
    Block GetBlock(int index,bool& state) const;
private:
    std::list<Block> element_container;
    };
}
#endif
