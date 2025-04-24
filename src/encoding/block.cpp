#include "mindev/include/encoding/block.h"
#include "mindev/include/encoding/encoder.h"
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
    bool Block::BuildBlockByTypeLengthBuffer(const VlInt& tlvType,const VlInt& tlvLength,std::vector<char>& buffer,bool verifyLength){
        
        this->tlvType = tlvType;
        this->length = tlvLength;
        this->elements = std::make_shared<ElementContainer>();
        if(verifyLength && this->GetLength()!=buffer.size()){
            return false;
        }
        Encoder encoder = Encoder();
        if(encoder.EncoderReset(SizeT(tlvType.GetSize()+tlvLength.GetSize()+buffer.size()), SizeT(0))){
            return false;
        }
        if(encoder.PrependByteArray(buffer, SizeT(buffer.size()))<0){
            return false;
        }
        if(encoder.PrependVarNumber(tlvLength)<0){
            return false;
        }
        if(encoder.PrependVarNumber(tlvType)<0){
            return false;
        }
        auto encodedBuffer = encoder.GetBuffer();
        if(encodedBuffer.size()==0){
            return false;
        }
        this->raw = encodedBuffer;
        this->value = buffer;
        return true;
    }
}