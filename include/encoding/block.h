#ifndef BLOCK_H_
#define BLOCK_H_

#include "vlint.h"
#include "elementcontainer.h"
#include "tlv.h"
#include <optional>

namespace mindev::encoding{
    class Encoder;
    class Block{
        private:
            VlInt tlvType; //TLV-Type
            VlInt length;//TLV-Length
            std::vector<char> value; //    TLV-Value
            ElementContainer elements;// TLV-sub-elements
            std::vector<char> raw; //TLV编码后的字节数组
        public:
            static std::optional<Block> DebugCreateBlockByBuffer(const std::vector<char> &buffer, bool verifyLength){
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
                res.tlvType = tlvType;
                res.length = tlvLength;
                res.raw = buffer;
                res.value = std::vector<char>(buffer.begin()+tlvType.GetSize()+tlvLength.GetSize(),buffer.end()); 
//                 if(!res.BuildBlockByTypeLengthBuffer(tlvType, tlvType+tlvLength, buffer, verifyLength)){
//                     return std::nullopt;
//                 }
                return res;
            }
            typedef std::shared_ptr<Block> ptr;
            Block(){
                this->value.clear();
                this->tlvType = mindev::encoding::VlInt(mindev::encoding::TLV::TlvInvalid);
                this->length = mindev::encoding::VlInt(0);
                this->raw.clear();
            };
            static std::optional<Block> CreateBlockByBuffer(std::vector<char>& buffer,bool verifyLength);
            static std::optional<Block> CreateBlockByTypeLengthBuffer(VlInt& tlvType,VlInt& tlvLength, std::vector<char>& buffer, bool verifyLength);
            inline VlInt& GetType(){return tlvType;} 
            inline void SetType(const VlInt& tlvType) {this->tlvType = tlvType;}
            inline std::vector<char>& GetValue(){return value;};
            inline void SetValue(const std::vector<char>& value){this->value=value;};
            inline VlInt& GetLength(){return length;};
            inline void SetLength(const VlInt& length){this->length = length;};
            inline std::vector<char>& GetRaw() {return this->raw;};
            std::optional<SizeT> GetSize() ;
            inline ElementContainer& GetSubElements(){return this->elements;};
            inline std::optional<Block> GetElement(const VlInt& tlvType){return this->elements.GetFirstBlockByType(const_cast<VlInt&>(tlvType));};
            inline void RemoveElement(VlInt& tlvType){this->elements.RemoveElements(tlvType);};
            inline void AddElement(const Block& block){this->elements.AddElement(block);};
            inline bool HasValue()const{return this->value.size()!=0;};
            inline bool HasRaw()const{return this->raw.size()!=0;};
            inline bool HasSubElement()const{return this->elements.Length()!=0;};
            inline bool IsValid()const{
                return this->tlvType != mindev::encoding::TLV::TlvInvalid;
            };
            inline void ClearElements(){this->elements.Clear();};
            bool ParseSubElements();
            int Encode(Encoder& encoder);
            bool BuildBlockByTypeLengthBuffer(const VlInt& tlvType,const VlInt& tlvLength,const std::vector<char>& buffer,bool verifyLength);
    };
}
#endif