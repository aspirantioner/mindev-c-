#ifndef VLINT_H_
#define VLINT_H_

#include <climits>
#include <vector>
#include "mindev/include/common/bigint.h"
#include "mindev/include/common/templateinit.h"

namespace mindev::encoding {
    class SizeT;
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
    VlInt(){};
    template <typename T>
	VlInt(const T& value);
    static int SizeOfVarNumber(const bigint& bignum);
    inline int GetSize() const {return this->size;}
    inline bigint GetVlIntValue() const {return this->VlIntValue;}
    inline std::vector<char> GetVlIntBytes()const {return this->VlIntBytes;}
    inline bool IsValidVlIntBytes(){return IsValidVlIntBytes(this->VlIntBytes);}
    inline bool IsValidVlIntValue(){return this->IsValidVlIntValue(this->VlIntValue);}
    inline bool IsInitial(){return this->size>0;}
    template<typename T>
    bool operator > (const T n) const{
        if constexpr(std::is_base_of_v<VlInt,T>){
            return this->GetVlIntValue()>n.GetVlIntValue();
        }
        return this->GetVlIntValue()>n;
    }
    template<typename T>
    VlInt operator + (const T val){
         if constexpr(std::is_same_v<T,VlInt>){
            return VlInt(this->GetVlIntValue()+val.GetVlIntValue());
        }
        return VlInt(this->GetVlIntValue()+val);
    }
    template<typename T>
    bool operator <= (const T n) const{
        if constexpr(std::is_same_v<T,VlInt>){
            return this->GetVlIntValue()<=n.GetVlIntValue();
        }
        return this->GetVlIntValue()<=n;
    }
    template<typename T>
    bool operator != (const T n) const{
        if constexpr(std::is_base_of_v<VlInt,T>){
            return this->GetVlIntValue()!=n.GetVlIntValue();
        }
        return this->GetVlIntValue()!=n;
    }
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