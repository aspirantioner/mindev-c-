#include "mindev/include/encoding/block.h"
#include "mindev/include/encoding/encoder.h"
#include "mindev/include/encoding/tlv.h"

namespace mindev::encoding {
    std::optional<Block> Block::CreateBlockByBuffer(std::vector<char> &buffer, bool verifyLength){
        auto tlvType = TLV::ReadType(buffer, VlInt(0));
        if(!tlvType.IsInitial()){
            std::runtime_error("buffer can't construct Block!");
        }
        auto tlvLength = TLV::ReadVarNumber(buffer, VlInt(tlvType.GetSize()));
        if(!tlvLength.IsInitial()){
            std::runtime_error("tlvLength read error!");
        }
        Block res;
        if(res.BuildBlockByTypeLengthBuffer(tlvType, tlvLength, buffer, verifyLength)==-1){
            return std::nullopt;
        }
        return res;
    }
    std::optional<Block> Block::CreateBlockByTypeLengthBuffer(const VlInt& tlvType,const VlInt& tlvLength, std::vector<char> &buffer, bool verifyLength){
        Block res;
        if(res.BuildBlockByTypeLengthBuffer(tlvType, tlvLength, buffer, verifyLength)==-1){
            return std::nullopt;
        }
        return res;
    }
    bool Block::BuildBlockByTypeLengthBuffer(const VlInt& tlvType,const VlInt& tlvLength,std::vector<char>& buffer,bool verifyLength){
        
        this->tlvType = tlvType;
        this->length = tlvLength;
        this->elements = ElementContainer();
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
    std::optional<SizeT> Block::GetSize() const{
        if(!IsValid()){
            return std::nullopt;
        }
        return SizeT(this->tlvType.GetSize()+this->length.GetSize()+this->value.size());
    }
    bool Block::ParseSubElements(){
        if(this->value.size()==0 || this->elements.Length()!=0){
            return true;
        }
        for(int start=0;start<this->value.size();){
            auto tlvType = TLV::ReadType(this->value, VlInt(start));
            if(!tlvType.IsInitial()){
                this->ClearElements();
                return false;
            }
            start+=tlvType.GetSize();
            auto tlvLength = TLV::ReadVarNumber(this->value, VlInt(start));
            if(!tlvLength.IsInitial()){
                this->ClearElements();
                return false;
            }
            start+=tlvLength.GetSize();
            if(tlvLength+start>this->value.size()){
                this->ClearElements();
                return false;
            }
            auto len = bigint::_bigint_to<int>(tlvLength.GetVlIntValue());
            std::vector<char> subBlockValue(len);
            std::copy(this->value.begin()+start,this->value.begin()+start+len,subBlockValue.begin());
            auto block = CreateBlockByTypeLengthBuffer(tlvType, tlvLength,subBlockValue,true);
            if(!block.has_value()){
                this->ClearElements();
                return false;
            }
            this->AddElement(block.value());
            start+=len;
        }
        return true;
    };
    int Block::Encode(Encoder& encoder){
        if(this->HasRaw()){
            return encoder.PrependByteArray(this->raw, SizeT(this->raw.size()));
        }
        
        int res = 0;
        if(this->HasValue()){
            auto tmplen = encoder.PrependByteArray(this->value, SizeT(this->value.size()));
            if(tmplen<=0){
                return -1;
            }
            res+=tmplen;
        }
        else{
            for(auto subBlock:this->elements.GetElements()){
                auto tmplen = subBlock.Encode(encoder);
                if(tmplen<=0){
                    return -1;
                }
                res+=tmplen;
            }
        }
        auto tmplen = encoder.PrependVarNumber(VlInt(res));
        if(tmplen<=0){
            return -1;
        }
        res+=tmplen;
        
        tmplen = encoder.PrependVarNumber(this->tlvType);
        if(tmplen<=0){
            return -1;
        }
        res+=tmplen;
        return res;
    };
}