#ifndef BLOCK_H_
#define BLOCK_H_

#include "vlint.h"
#include "elementcontainer.h"

namespace mindev::encoding{
    class ElementContainer;
    class Block{
        private:
            VlInt tlvType; //TLV-Type
            VlInt Length;//TLV-Length
            std::vector<unsigned char> values; //    TLV-Value
            std::shared_ptr<ElementContainer> elements;// TLV-sub-elements
            std::vector<unsigned char> raw; //TLV编码后的字节数组
        public:
            typedef std::shared_ptr<Block> ptr;
            Block();
            ~Block();
    };
}
#endif