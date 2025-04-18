
#ifndef IDENTIFIERCOMPONENT_H_
#define IDENTIFIERCOMPONENT_H_
#include "mindev/include/encoding/iencodingable.h"
#include "mindev/include/encoding/block.h"
#include "tlvcomponentbase.h"
#include <cstdint>

namespace mindev::component{
    class IdentifierComponent{
private:
    mindev::encoding::Block::ptr identifierBlock;    
    uint8_t marker;
    std::string stringValue;
    long intValue;
    std::vector<char> byteArrayValue;
    static const uint8_t MarkerString = 0x00;
    static const uint8_t MarkerNonNegativeInteger = 0x01;
    static const uint8_t MarkerByteArray = 0x02;
    static const uint8_t MarkerVersionNumber = 0x03;
    static const uint8_t MarkerFragmentNumber = 0x04;
    };
}

#endif
