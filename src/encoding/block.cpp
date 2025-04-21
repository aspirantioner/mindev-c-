#include "mindev/include/encoding/block.h"
#include "mindev/include/encoding/tlv.h"

namespace mindev::encoding {
    Block::Block(const std::vector<char> &buffer, bool verifyLength){
        auto tlvType = TLV::ReadType(buffer, VlInt(0));
        if(!tlvType.IsInitial()){
            std::runtime_error("buffer can't construct Block!");
        }
        auto tlvLength = TLV::ReadVarNumber(buffer, VlInt(tlvType.GetSize()));
        if(!tlvLength.IsInitial()){
            std::runtime_error("tlvLength read error!");
        }
        
    }
    void Block::BuildBlockByTypeLengthBuffer(const VlInt& tlvType,const VlInt& tlvLength,const std::vector<char>& buffer,bool verifyLength){
        
        this->tlvType = tlvType;
        this->Length = tlvLength;
        this->elements = std::make_shared<ElementContainer>();
        
    }
}