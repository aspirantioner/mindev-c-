#ifndef VLINT_H_
#define VLINT_H_

#include <climits>
#include <cstdint>
#include <vector>
#include "mindev/include/common/bigint.hpp"
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
    
    static const unsigned char uint8Max = UCHAR_MAX;
    static const unsigned short uint16Max = USHRT_MAX;
    static const unsigned long uint32Max = UINT32_MAX;
    static const unsigned long long uint64Max = ULLONG_MAX;
    VlInt(){};
    template <typename T>
	VlInt(T value){
        if constexpr (std::is_same_v<T, std::vector<char>>){
            if(IsValidVlIntBytes(value)){
               this->VlIntBytes =  value;
               this->VlIntValue =  VlintBytesToBigInter(this->VlIntBytes);
               this->size = SizeOfVarNumber(this->VlIntValue); 
            }
        } else if constexpr(std::is_same_v<T,bigint>) {
            if(IsValidVlIntValue(value)){
                this->VlIntValue = value;
                this->VlIntBytes = BigInterToVlintBytes(value);
                this->size = SizeOfVarNumber(this->VlIntValue);
            }
        } else if constexpr(std::is_base_of<VlInt,T>::value) {
            if(value.IsInitial()){
                this->VlIntValue = value.GetVlIntValue();
                this->VlIntBytes = value.GetVlIntBytes();
                this->size = value.GetSize();
            }
        } else if constexpr(std::is_integral_v<T>) {
            bigint num = bigint::_to_bigint(value);
            if(IsValidVlIntValue(num)){
                this->VlIntValue = num;
                this->VlIntBytes = BigInterToVlintBytes(this->VlIntValue);
                this->size = SizeOfVarNumber(num);
            }
        } else{
            static_assert(always_false<T>,"unsported type to init !");
        }
    }
    static int SizeOfVarNumber(const bigint& bignum);
    inline int GetSize() const {return this->size;}
    inline bigint GetVlIntValue() const {return this->VlIntValue;}
    inline std::vector<char> GetVlIntBytes() const {return this->VlIntBytes;}
    inline bool IsValidVlIntBytes(){return IsValidVlIntBytes(this->VlIntBytes);}
    inline bool IsValidVlIntValue(){return this->IsValidVlIntValue(this->VlIntValue);}
    inline bool IsInitial(){return this->size>0;}
    template<typename T>
    bool operator > (T n){
        if constexpr(std::is_base_of_v<VlInt,T>){
            return this->GetVlIntValue()>n.GetVlIntValue();
        }else if constexpr(std::is_integral_v<T>){
            return this->GetVlIntValue()>n;
        }else{
            static_assert(always_false<T>, "Unsupported type in VlInt::operator+");
        }
    }
    template<typename T>
    VlInt operator + (T val){
        if constexpr(std::is_same_v<T,VlInt>){
            return VlInt(this->GetVlIntValue()+val.GetVlIntValue());
        }else if constexpr(std::is_integral_v<T>){
            return VlInt(this->GetVlIntValue()+val);
        }else{
            static_assert(always_false<T>, "Unsupported type in VlInt::operator+");
        }
    }
    template<typename T>
    bool operator <= (T n) {
        if constexpr(std::is_same_v<T,VlInt>){
            return this->GetVlIntValue()<=n.GetVlIntValue();
        }else if constexpr(std::is_integral_v<T>){
            return this->GetVlIntValue()<=n;
        }else{
            static_assert(always_false<T>, "Unsupported type in VlInt::operator+");
        }
    }
    template<typename T>
    bool operator != (T n) {
        if constexpr(std::is_base_of_v<VlInt,T>){
            return this->GetVlIntValue()!=n.GetVlIntValue();
        }else if constexpr(std::is_integral_v<T>){
            return this->GetVlIntValue()!=n;
        }else{
            static_assert(always_false<T>, "Unsupported type in VlInt::operator+");
        }
    }
    template<typename T>
    bool operator == (T n){
        if constexpr(std::is_base_of_v<VlInt,T>){
            return this->GetVlIntValue()==n.GetVlIntValue();
        }else if constexpr(std::is_integral_v<T>){
            return this->GetVlIntValue()==n;
        }else{
            static_assert(always_false<T>, "Unsupported type in VlInt::operator+");
        }
    }
protected:
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