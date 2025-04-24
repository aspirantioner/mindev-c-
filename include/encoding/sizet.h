#ifndef SIZET_H_
#define SIZET_H_

#include "mindev/include/encoding/vlint.h"
namespace mindev::encoding {
    class SizeT :public VlInt{
public:
        using VlInt::VlInt;
        SizeT(){};
        template <typename T>
	    SizeT(const T& value):VlInt(value){};
        template<typename T>
        SizeT operator + (const T val) const {
            if constexpr(std::is_same_v<T,SizeT> || std::is_same_v<T, VlInt>){
                return SizeT(this->GetVlIntValue()+val.GetVlIntValue());
            }
            return SizeT(this->GetVlIntValue()+val);
        }
        SizeT operator + (const SizeT& val) const {
            return SizeT(this->GetVlIntValue()+val.GetVlIntValue());
        }
    };
}


#endif