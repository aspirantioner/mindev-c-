#ifndef BLOCK_H_
#define BLOCK_H_

#include "vlint.h"
#include "elementcontainer.h"

namespace mindev::encoding{
    class ElementContainer;
    class Block{
        private:
            VlInt tlvType; //TLV-Type
            VlInt length;//TLV-Length
            std::vector<char> value; //    TLV-Value
            std::shared_ptr<ElementContainer> elements;// TLV-sub-elements
            std::vector<char> raw; //TLV编码后的字节数组
        public:
            typedef std::shared_ptr<Block> ptr;
            Block(){};
            Block(const std::vector<char>& buffer,bool verifyLength);
            inline VlInt GetType()const{return tlvType;} 
            inline std::vector<char> GetValue()const{return value;};
            inline VlInt GetLength()const{return length;};
            bool BuildBlockByTypeLengthBuffer(const VlInt& tlvType,const VlInt& tlvLength,std::vector<char>& buffer,bool verifyLength);
    };
}
#endif