#include "mindev/include/encoding/elementcontainer.h"
#include <algorithm> 
namespace mindev::encoding {
    void ElementContainer::RemoveElements(const VlInt& tlvType){
        element_container.remove_if([tlvType](Block& block){return tlvType.GetVlIntValue() == block.GetType().GetVlIntValue();});
    }
    Block ElementContainer::GetBlock(int index,bool& state) const{
        if(index<0 || index>=element_container.size()){
            state = false;
            return Block();
        }
        auto it = element_container.begin();
        std::advance(it, index);
        state = true;
        return *it;
    };
    Block ElementContainer::GetFirstBlockByType(VlInt tlvType,bool& state) const{
        auto it = std::find_if(element_container.begin(),element_container.end(),[tlvType](const Block& block){return block.GetType().GetVlIntValue()==tlvType.GetVlIntValue();});
        if(it == element_container.end()){
            state = false;
            return Block();
        }
        state = true;
        return *it;
    }
}