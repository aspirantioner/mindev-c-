#ifndef ELEMENTCONTAINER_H_
#define ELEMENTCONTAINER_H_

#include "mindev/include/encoding/vlint.h"
#include <optional>
namespace mindev::encoding { class Block; }
namespace mindev::encoding{
    class ElementContainer {
public:
    typedef std::shared_ptr<ElementContainer> ptr;
    ElementContainer(){};
    inline std::vector<Block>& GetElements() {return element_container;}
    inline int Length()const{return element_container.size();}
    inline void Clear(){element_container.clear();}
    inline void AddElement(const Block& block){element_container.emplace_back(block);}
    void RemoveElements(const VlInt& tlvType);
    std::optional<std::reference_wrapper<Block>> GetBlock(int index) const;
    std::optional<std::reference_wrapper<Block>> GetFirstBlockByType(const VlInt& tlvType) const;
private:
    std::vector<Block> element_container;
    };
}
#endif
