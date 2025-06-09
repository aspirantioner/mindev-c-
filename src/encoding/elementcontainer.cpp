#include "mindev/include/encoding/elementcontainer.h"
#include <algorithm> 
#include "mindev/include/encoding/block.h"

namespace mindev::encoding {
    void ElementContainer::RemoveElements(VlInt& tlvType){
        element_container.erase(
            std::remove_if(element_container.begin(), element_container.end(), [&tlvType](Block& block){return tlvType.GetVlIntValue() == block.GetType().GetVlIntValue();}),
            element_container.end()
        );
    }
    
    std::optional<std::reference_wrapper<Block>> ElementContainer::GetBlock(int index){
        if(index<0 || index>=element_container.size()){
            return std::nullopt;
        }
        auto it = element_container.begin();
        std::advance(it, index);
        return std::ref(*it);
    };
    std::optional<std::reference_wrapper<Block>> ElementContainer::GetFirstBlockByType(VlInt& tlvType) {
        for(auto iter = element_container.begin();iter!=element_container.end();iter++){
            if(iter->GetType().GetVlIntValue()==tlvType.GetVlIntValue()){
                return std::ref(*iter);
            }
        }
        return std::nullopt;
//         auto it = std::find_if(element_container.begin(),element_container.end(),[&tlvType](Block& block){return block.GetType().GetVlIntValue()==tlvType.GetVlIntValue();});
//         if(it == element_container.end()){
//             return std::nullopt;
//         }
//         return it;
    }
}