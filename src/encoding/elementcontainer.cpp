#include "mindev/include/encoding/elementcontainer.h"
#include <algorithm> 
namespace mindev::encoding {
    void ElementContainer::RemoveElements(const VlInt& tlvType){
        element_container.remove_if([tlvType](Block& block){return tlvType.GetVlIntValue() == block.GetType().GetVlIntValue();});
    }
    
    std::optional<std::reference_wrapper<Block>> ElementContainer::GetBlock(int index) const{
        if(index<0 || index>=element_container.size()){
            return std::nullopt;
        }
        auto it = element_container.begin();
        std::advance(it, index);
        Block block = *it;
        return block;
    };
    std::optional<std::reference_wrapper<Block>> ElementContainer::GetFirstBlockByType(const VlInt& tlvType) const{
        auto it = std::find_if(element_container.begin(),element_container.end(),[tlvType](const Block& block){return block.GetType().GetVlIntValue()==tlvType.GetVlIntValue();});
        if(it == element_container.end()){
            return std::nullopt;
        }
        Block block = *it;
        return block;
    }
}