#include "mindev/include/encoding/tlv.h"
#include "mindev/include/common/byteutils.h"

namespace mindev::encoding {
    int TLV::SizeOfNonNegativeInteger(long v){
        if(v<=VlInt::uint8Max){
            return 1;
        } else if (v<=VlInt::uint16Max) {
                return 2;
        } else if (v<=VlInt::uint32Max) {
            return 4;
        }else{
            return 8;
        }
    }
    VlInt TLV::ReadVarNumber(const std::vector<char>& buffer,const VlInt& start){
        VlInt res = VlInt();
        auto length = bigint::_to_bigint(std::to_string(buffer.size()));
        
        if(static_cast<bigint>(const_cast<VlInt&>(start).GetVlIntValue())>=length){
            return res;
        }
        auto index = bigint::_bigint_to<int>(const_cast<VlInt&>(start).GetVlIntValue());
        if(index<0 || index>=buffer.size()){
            return res;
        }
        
        int firstbyte = byteutils::ToValue<int>(buffer,index);
        if(firstbyte<241){
            return VlInt(firstbyte);
        } else if (firstbyte==VlInt::VlIntExtend2) {
            
            if(buffer.size()-index<VlInt::VlIntSize3){
                return res;
            }
            return VlInt(std::vector<char>(buffer.begin()+index,buffer.begin()+index+VlInt::VlIntSize3));
        } else if (firstbyte==VlInt::VlIntExtend4) {
            if(buffer.size()-index<VlInt::VlIntSize5){
                return res;
            }
            return VlInt(std::vector<char>(buffer.begin()+index,buffer.begin()+index+VlInt::VlIntSize5));
        } else if (firstbyte==VlInt::VlIntExtend8) {
            if(buffer.size()-index<VlInt::VlIntSize9){
                return res;
            }
            return VlInt(std::vector<char>(buffer.begin()+index,buffer.begin()+index+VlInt::VlIntSize9));
        }
        return res;
    }
    VlInt TLV::ReadType(const std::vector<char>& buffer,const VlInt& start){
        auto tlvtype = ReadVarNumber(buffer, const_cast<VlInt&>(start));
        
        if(!tlvtype.IsInitial()||static_cast<bigint>(tlvtype.GetVlIntValue())==bigint::_to_bigint(TLV::TlvInvalid)||static_cast<bigint>(tlvtype.GetVlIntValue())>bigint::_to_bigint(TLV::MaxTlvNum)){
            return VlInt();
        }
        return tlvtype;
    }
    long TLV::ReadNonNegativeInteger(const std::vector<char>& buffer,int start,int end){
        if(start<0 || end>buffer.size() || start == end){
            return -1;
        }
        auto new_buffer = std::vector<char>(buffer.begin()+start,buffer.begin()+end);
        long res = -1;
        switch (new_buffer.size()) { 
            case sizeof(u_int8_t):
                res = byteutils::ToValue<u_int8_t>(new_buffer);
                break;
            case sizeof(u_int16_t):
                res = byteutils::ToValue<u_int16_t>(new_buffer);
                break;
            case sizeof(u_int32_t):
                res = byteutils::ToValue<u_int32_t>(new_buffer);
                break;
            case sizeof(u_int64_t):
                res = byteutils::ToValue<u_int64_t>(new_buffer);
                break;
        }
        return res;
    }
}