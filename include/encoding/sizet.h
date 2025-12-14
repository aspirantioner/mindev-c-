#ifndef SIZET_H_
#define SIZET_H_

#include "mindev/include/encoding/vlint.h"
#include "mindev/include/common/templateinit.h"

namespace mindev::encoding {
    class SizeT :public VlInt,public TemplateInit{
public:
        using VlInt::VlInt;
        SizeT(){};
        template <typename T>
	    SizeT(const T value):VlInt(value){};
        template<typename T>
        SizeT operator + (T val) {
            if constexpr(std::is_base_of<VlInt,T>::value){
                return SizeT(this->GetVlIntValue()+val.GetVlIntValue());
            }else if constexpr(std::is_integral_v<T>){
                return this->GetVlIntValue()+val;
            }else{
                static_assert(always_false<T>, "Unsupported type in VlInt::operator+");
            }
        }
    };
}


#endif