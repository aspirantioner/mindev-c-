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
            typedef std::shared_ptr<Block> ptr;
            Block(){};
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
            inline bool IsValid(){
                long long int val = 1;
                return this->tlvType != val;
            };
            inline void ClearElements(){this->elements.Clear();};
            bool ParseSubElements();
            int Encode(Encoder& encoder);
            bool BuildBlockByTypeLengthBuffer(VlInt& tlvType,VlInt& tlvLength,std::vector<char>& buffer,bool verifyLength);
    };
}
#endif