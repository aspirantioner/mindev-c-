#ifndef MUTABLEATTRFIELD_H_
#define MUTABLEATTRFIELD_H_

#include "mindev/include/encoding/block.h"
#include "mindev/include/encoding/elementcontainer.h"

namespace mindev::component{
    class MutableAttrField{
protected:
    mindev::encoding::ElementContainer blocks;    
public:
    MutableAttrField(){}
    inline void ClearBlocks(){
        this->blocks.Clear();
    }
    inline mindev::encoding::ElementContainer& GetBlocks(){return this->blocks;}
    inline void AddBlock(const mindev::encoding::Block& block){this->blocks.AddElement(block);}
    inline std::optional<std::reference_wrapper<mindev::encoding::Block>> GetBlock(int index) {
        return this->blocks.GetBlock(index);
    }
    inline std::optional<std::reference_wrapper<mindev::encoding::Block>> GetFirstBlockByType(const mindev::encoding::VlInt& tlvType) {
        return this->blocks.GetFirstBlockByType(const_cast<mindev::encoding::VlInt&>(tlvType));
    }
    };
}

#endif