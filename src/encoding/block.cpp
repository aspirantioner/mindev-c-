#include "mindev/include/encoding/block.h"
#include "mindev/include/encoding/encoder.h"
#include "mindev/include/encoding/tlv.h"

namespace mindev::encoding {
    std::optional<Block> Block::CreateBlockByBuffer(std::vector<char> &buffer, bool verifyLength){
        auto tmp = VlInt(0);
        auto tlvType = TLV::ReadType(buffer, tmp);
        if(!tlvType.IsInitial()){
            return std::nullopt;
        }
        auto val = tlvType.GetSize();
        tmp = VlInt(val);
        auto tlvLength = TLV::ReadVarNumber(buffer, tmp);
        if(!tlvLength.IsInitial()){
            return std::nullopt;
        }
        Block res;
        std::vector<char> encode_data(buffer.begin()+tlvType.GetSize()+tlvLength.GetSize(),buffer.end());
        if(!res.BuildBlockByTypeLengthBuffer(tlvType, tlvLength, encode_data, verifyLength)){
            return std::nullopt;
        }
        return res;
    }
    std::optional<Block> Block::CreateBlockByTypeLengthBuffer(VlInt& tlvType,VlInt& tlvLength, std::vector<char> &buffer, bool verifyLength){
        Block res;
        if(!res.BuildBlockByTypeLengthBuffer(tlvType, tlvLength, buffer, verifyLength)){
            return std::nullopt;
        }
        return res;
    }
    bool Block::BuildBlockByTypeLengthBuffer(const VlInt& tlvType,const VlInt& tlvLength,const std::vector<char>& buffer,bool verifyLength){
        
        this->tlvType = tlvType;
        this->length = tlvLength;
        this->elements = ElementContainer();
        if(verifyLength && this->GetLength()!=buffer.size()){
            return false;
        }
        Encoder encoder = Encoder();
        auto size1 = SizeT(tlvType.GetSize()+tlvLength.GetSize()+buffer.size());
        auto size2 = SizeT(0);
        if(!encoder.EncoderReset(size1,size2)){
            return false;
        }
        auto tmp = SizeT(buffer.size());
        if(encoder.PrependByteArray(buffer,tmp)<0){
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
    std::optional<SizeT> Block::GetSize() {
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
            auto origin_start = start;
            auto tmp = VlInt(start);
            auto tlvType = TLV::ReadType(this->value, tmp);
            if(!tlvType.IsInitial()){
                this->ClearElements();
                return false;
            }
            start+=tlvType.GetSize();
            tmp = VlInt(start);
            auto tlvLength = TLV::ReadVarNumber(this->value, tmp);
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
            //Debug:
            Block block;
            block.tlvType = tlvType;
            block.length = tlvLength;
            block.value = subBlockValue;
            block.raw = std::vector<char>(this->value.begin()+origin_start,this->value.begin()+start+len);
            this->AddElement(block);
//             auto block = CreateBlockByTypeLengthBuffer(tlvType, tlvLength,subBlockValue,true);
//             if(!block.has_value()){
//                 this->ClearElements();
//                 return false;
//             }
//             this->AddElement(block.value());
            start+=len;
        }
        return true;
    };
    int Block::Encode(Encoder& encoder){
        if(this->HasRaw()){
            auto tmp = SizeT(this->raw.size());
            return encoder.PrependByteArray(this->raw, tmp);
        }
        
        int res = 0;
        if(this->HasValue()){
            auto tmp = SizeT(this->value.size());
            auto tmplen = encoder.PrependByteArray(this->value, tmp);
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
        auto tmp = VlInt(res);
        auto tmplen = encoder.PrependVarNumber(tmp);
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