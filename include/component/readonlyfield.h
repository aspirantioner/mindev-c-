#ifndef READONLYFIELD_H_
#define READONLYFIELD_H_

#include "mindev/include/encoding/iencodingable.h"
#include "tlvcomponentbase.h"

namespace mindev::component{
    class ReadOnlyField:public TlvComponentBase,public mindev::encoding::IEncodingAble{
public:
    ReadOnlyField(){}
    inline void AddBlock(const mindev::encoding::Block& block){
        this->blocks.AddElement(block);
    }
    inline void ClearBlocks(){this->blocks.Clear();}
    inline mindev::encoding::ElementContainer& GetBlocks(){return this->blocks;}
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    mindev::encoding::ElementContainer blocks ;
    };
}

#endif
