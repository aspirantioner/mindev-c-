#include "mindev/include/encoding/vlint.h"
#include "mindev/include/common/byteutils.h"
#include <bits/alltypes.h>

namespace mindev::encoding {
    int VlInt::SizeOfVarNumber(const bigint& bignum){
        if(bignum<VlIntExtend2){
            return 1;
        }
        else if(bignum<uint16Max){
            return 3;
        }
        else if(bignum<uint32Max){
            return 5;
        }
        else if(bignum<uint64Max){
            return 9;
        }
        else{
            return -1;
        }
    }
    bool VlInt::IsValidVlIntBytes(const std::vector<char>& vlIntBytes){
        if(vlIntBytes.size()<1){
            return false;
        }
        int firstByteValue =  vlIntBytes[0]&0xff;
        if(vlIntBytes.size()==1 && firstByteValue<=240){
            return true;
        } else if (vlIntBytes.size()==3 && firstByteValue==VlInt::VlIntExtend2) {
            return true;
        } else if (vlIntBytes.size()==5 && firstByteValue==VlInt::VlIntExtend4) {
            return true;
        } else if (vlIntBytes.size() == 9 && firstByteValue == VlInt::VlIntExtend8) {
            return true;
        }
        return false;
    }
    bool VlInt::IsValidVlIntValue(const bigint& value){
        static const  bigint max_bigint = bigint(bigint(2^63)*bigint(2));
        if(value<0){
            return false;
        }
        if(value>max_bigint){
            return false;
        }
        return true;
    }
    bigint VlInt::VlintBytesToBigInter(const std::vector<char>& vlIntBytes){
        bigint res;
        long value = 0;
        if(vlIntBytes.size()==1){
            value = byteutils::ToValue<u_int8_t>(vlIntBytes,0,false);
        } else if (VlIntBytes.size()==3) {
            value = byteutils::ToValue<u_int16_t>(vlIntBytes,1,false);
        } else if (VlIntBytes.size()==5) {
            value = byteutils::ToValue<u_int32_t>(VlIntBytes,1,false);
        } else if (VlIntBytes.size()==9) {
            value = byteutils::ToValue<u_int64_t>(VlIntBytes,1,false);
        }
        return bigint::_to_bigint(value);
    }
    std::vector<char> VlInt::BigInterToVlintBytes(const bigint& value){
        std::vector<char> res;
        auto size = SizeOfVarNumber(value);
        if(size==1){
            res = byteutils::FromValue(bigint::_bigint_to<uint8_t>(value));
        } else if (size == 3) {
            res = byteutils::FromValue(bigint::_bigint_to<uint16_t>(value));
            res.insert(res.begin(),static_cast<char>(VlInt::VlIntExtend2));
        } else if (size == 5) {
            res = byteutils::FromValue(bigint::_bigint_to<uint32_t>(value));
            res.insert(res.begin(),static_cast<char>(VlInt::VlIntExtend4));
        } else if (size == 9) {
            res = byteutils::FromValue(bigint::_bigint_to<uint32_t>(value));
            res.insert(res.begin(),static_cast<char>(VlInt::VlIntExtend8));
        }
        return res;
    }
}

// /**
//      * 传入的应是一个有效的变长整型数组
//      * @param vlIntBytes
//      */
//     public VlInt(byte[] vlIntBytes){
//         if(!isValidVlIntBytes(vlIntBytes)){
//             throw new Error("VlInt(byte[] bytes): VlIntBytes is invalid.");
//         }
//         this.VlIntBytes=vlIntBytes;
//         this.VlIntValue=vlintBytes2bigInteger(vlIntBytes);
//         this.size = SizeOfVarNumber(this.VlIntValue);
//     }
//
//     /**
//      * 传入的应是一个有效的变长整型value
//      * @param bigInteger
//      */
//     public VlInt(BigInteger bigInteger){
//         if(!isValidVlIntValue(bigInteger)){
//             throw new Error("VlInt(BigInteger bigInteger): VlIntValue is invalid.");
//         }
//         this.VlIntValue=bigInteger;
//         this.VlIntBytes=bigInteger2vlintBytes(bigInteger);
//         this.size=SizeOfVarNumber(this.VlIntValue);
//     }
//
//     public VlInt(SizeT sizeT){
//         if(!sizeT.isInitial()){
//             throw new Error("VlInt(SizeT sizeT): The sizeT is invalid, it should be initial.");
//         }
//         this.VlIntBytes=sizeT.getVlIntBytes();
//         this.VlIntValue=sizeT.getVlIntValue();
//         this.size = sizeT.size();
//     }
//
//     public VlInt(VlInt vlInt){
//         if(!vlInt.isInitial()){
//             throw new Error("VlInt vlInt: The vlInt is invalid, it should be initial.");
//         }
//         this.VlIntBytes=vlInt.getVlIntBytes();
//         this.VlIntValue=vlInt.getVlIntValue();
//         this.size = vlInt.size();
//     }

//     public VlInt(int i){
//         this.VlIntValue=BigInteger.valueOf(i);
//         if(!isValidVlIntValue(this.VlIntValue)){
//             throw new Error("VlInt(int i): The i value is invalid, it is out of the bound.");
//         }
//         this.VlIntBytes=bigInteger2vlintBytes(this.VlIntValue);
//         this.size=SizeOfVarNumber(this.VlIntValue);
//     }
//
//     public VlInt(long l){
//         this.VlIntValue=BigInteger.valueOf(l);
//         if(!isValidVlIntValue(this.VlIntValue)){
//             throw new Error("VlInt(long l): out of the bound, the l value is invalid.");
//         }
//         this.VlIntBytes=bigInteger2vlintBytes(this.VlIntValue);
//         this.size=SizeOfVarNumber(this.VlIntValue);
//     }
