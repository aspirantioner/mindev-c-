#ifndef VLINT_H_
#define VLINT_H_
#include <climits>
#include <vector>
#include "mindev/include/common/bigint.h"
#include "mindev/include/common/templateinit.h"

namespace mindev::encoding {
    class VlInt:public TemplateInit {
public:
    typedef std::shared_ptr<VlInt> ptr;
    static const int VlIntExtend2 = 241;
    static const int VlIntExtend4 = 242;
    static const int VlIntExtend8 = 243;
    
    static const int VlIntSize1 = 1;
    static const int VlIntSize3 = 3;
    static const int VlIntSize5 = 5;
    static const int VlIntSize9 = 9;
    
    static const long uint8Max = 2^8-1;
    static const long uint16Max = 2^16-1;
    static const long uint32Max = 2^32-1;
    static const long uint64Max = LONG_MAX;
    
    template <typename T>
	VlInt(const T& value);
    static int SizeOfVarNumber(const bigint& bignum);
    inline int GetSize(){return this->size;}
    inline bigint GetVlIntValue(){return this->VlIntValue;}
    inline std::vector<char> GetVlIntBytes(){return this->VlIntBytes;}
    inline bool IsValidVlIntBytes(){return IsValidVlIntBytes(this->VlIntBytes);}
    inline bool IsValidVlIntValue(){return this->IsValidVlIntValue(this->VlIntValue);}
    inline bool IsInitial(){return this->size>0;}
    
private:
    std::vector<char> VlIntBytes;
    int size = -1;
    bigint VlIntValue;
    bool IsValidVlIntBytes(const std::vector<char>& vlIntBytes);
    bool IsValidVlIntValue(const bigint& value);
    bigint VlintBytesToBigInter(const std::vector<char>& vlIntBytes);
    std::vector<char> BigInterToVlintBytes(const bigint& value);
    };
}

#endif