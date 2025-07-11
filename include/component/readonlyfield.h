#ifndef READONLYFIELD_H_
#define READONLYFIELD_H_

#include "mindev/include/encoding/iencodingable.h"
#include "tlvcomponentbase.h"
#include "mindev/include/encoding/vlint.h"
#include "mindev/include/encoding/block.h"
#include "mindev/include/encoding/elementcontainer.h"

namespace mindev::component{
    class ReadOnlyField:public TlvComponentBase,public mindev::encoding::IEncodingAble{
public:
    ReadOnlyField(){}
    inline void AddBlock(const mindev::encoding::Block& block){
        this->blocks.AddElement(block);
    }
    inline void ClearBlocks(){this->blocks.Clear();}
    inline mindev::encoding::ElementContainer& GetBlocks(){return this->blocks;}
    inline std::optional<std::reference_wrapper<mindev::encoding::Block>> GetBlockByType(const mindev::encoding::VlInt& tlvType){
        return this->blocks.GetFirstBlockByType(const_cast<mindev::encoding::VlInt&>(tlvType));
    }
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    mindev::encoding::ElementContainer blocks ;
    };
}

#endif
