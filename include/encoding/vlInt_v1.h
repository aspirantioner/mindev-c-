#ifndef VLINT_V1_H_
#define VLINT_V1_H_
#include <vector>
#include "vlint.h"

namespace mindev::encoding {
    class VlInt_V1{
private:
    std::vector<char> VlIntByte;
    long VlIntValue;
public:
    int SizeOfVarNumber(){
        if(VlIntValue<VlInt::VlIntExtend2){
            return VlInt::VlIntSize1;
        }
        else if(VlIntValue<2^16){
            return VlInt::VlIntSize3;
        }
        else{
            return VlInt::VlIntSize5;
        }
    }
    };
}

#endif