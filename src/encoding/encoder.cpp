#include "mindev/include/encoding/encoder.h"
#include "mindev/include/encoding/block.h"
#include <algorithm>
#include <cstdint>

namespace mindev::encoding {
    void Encoder::EstimatorReset(){
        this->left = 0;
        this->right = 1;
        this->isInitial = true;
        this->isEstimator = true;
        this->totalReserve = SizeT(LONG_MAX);
    }
    bool Encoder::EncoderReset(const SizeT& totalReverve,const SizeT& reserveFromBack){
        if(const_cast<SizeT&>(reserveFromBack).GetVlIntValue()>const_cast<SizeT&>(totalReverve).GetVlIntValue()){
            return false;
        }    
        auto len = bigint::_bigint_to<int>(const_cast<SizeT&>(totalReverve).GetVlIntValue());
        if(len<=0){
            return false;
        }
        this->buffer.resize(len);
        this->right = bigint::_bigint_to<int>(const_cast<SizeT&>(totalReverve).GetVlIntValue() - const_cast<SizeT&>(reserveFromBack).GetVlIntValue());
        this->left = this->right-1;
        this->isInitial = true;
        this->isEstimator = false;
        this->totalReserve = totalReverve;
        return true;
    }
    bool Encoder::Check(const SizeT& size){
        if(!this->isInitial){
            return false;
        }
        if(this->totalReserve>(this->Size()+size)){
            return false;
        }
        return true;
    }
    int Encoder::PrependByte(char value){
        if(this->isEstimator){
            this->left--;
            return 1;
        }
        if(Check(SizeT(1))){
            this->buffer[this->left] = value;
            this->left--;
            return 1;
        }
        return -1;
    }
    int Encoder::AppendByte(char value){
        if(this->isEstimator){
            this->right++;
            return 1;
        }
        if(Check(SizeT(1))){
            this->buffer[this->left] = value;
            this->right++;
            return 1;
        }
        return -1;
    }
    std::vector<char> Encoder::BuildNonNegativeIntegerArr(long uint64_value){
        if(uint64_value<=255){
            return std::vector<char>{(char)uint64_value};
        }
        VlInt vlInt = VlInt(uint64_value);
        return std::vector<char>(vlInt.GetVlIntBytes().begin()+1,vlInt.GetVlIntBytes().end());
    }
    int Encoder::PrependByteArray(std::vector<char>& array,const SizeT& size){
        if(Check(size) && const_cast<SizeT&>(size)<=int(array.size())){
            auto copy_len = bigint::_bigint_to<int>(const_cast<SizeT&>(size).GetVlIntValue());
            if(!this->isEstimator){
                std::copy(array.begin(),array.begin()+copy_len,this->buffer.begin()+this->left-copy_len+1);
            }
            this->left -= array.size();
            return copy_len;
        }
        return -1;
    }
    int Encoder::AppendByteArray(std::vector<char>& array,SizeT& size){
        if(Check(size) && size<=array.size()){
            auto copy_len = bigint::_bigint_to<int>(size.GetVlIntValue());
            if(!this->isEstimator){
                std::copy(array.begin(),array.begin()+copy_len,this->buffer.begin()+this->right);
            }
            this->right += array.size();
            return copy_len;
        }
        return -1;
    }
    int Encoder::AppendNonNegativeInteger(long uint64_value){
        auto bytes = BuildNonNegativeIntegerArr(uint64_value);
        auto tmp = SizeT(bytes.size());
        return this->AppendByteArray(bytes,tmp);
    }
    int Encoder::PrependNonNegativeInteger(long uint64_value){
        auto bytes = BuildNonNegativeIntegerArr(uint64_value);
        auto tmp = SizeT(bytes.size());
        return this->PrependByteArray(bytes,tmp);
    }
    int Encoder::PrependVarNumber(const VlInt& varNumber){
        auto temp = const_cast<VlInt&>(varNumber).GetVlIntBytes();
        auto tmp = SizeT(const_cast<VlInt&>(varNumber).GetSize());
        return this->PrependByteArray(temp, tmp);
    }
    int Encoder::AppendVarNumber(VlInt& varNumber){
        auto temp = varNumber.GetVlIntBytes();
        auto tmp = SizeT(varNumber.GetSize());
        return this->AppendByteArray(temp, tmp);
    }
    int Encoder::PrependByteArrayBlock(VlInt& tlvType,std::vector<char>& array,SizeT& size){
        int totalLength = this->PrependByteArray(array, size);
        auto tmp = VlInt(size);
        totalLength += this->PrependVarNumber(tmp);
        totalLength += this->PrependVarNumber(tlvType);
        return totalLength;
    }
    int Encoder::AppendByteArrayBlock(VlInt& tlvType,std::vector<char>& array,SizeT& size){
        int totalLength =this->PrependVarNumber(tlvType); 
        auto tmp = VlInt(size);
        totalLength += this->PrependVarNumber(tmp);
        totalLength += this->PrependByteArray(array, size);
        return totalLength;
    }
    int Encoder::PrependBlock(Block& block){
        auto temp = block.GetValue();
        auto tmp = SizeT(block.GetLength());
        return this->PrependByteArrayBlock(block.GetType(), temp, tmp);
    }
    int Encoder::AppendBlock(Block& block){
        auto temp = block.GetValue();
        auto tmp = SizeT(block.GetLength());
        return this->AppendByteArrayBlock(block.GetType(), temp, tmp);
    }
    std::vector<char> Encoder::GetBuffer() const {
        std::vector<char> res;
        if(!this->isInitial || this->isEstimator){
            return res;
        }
        res.resize(this->right-this->left-1);
        std::copy(res.begin(),res.end(),this->GetBuffer().begin()+this->left+1);
        return res;
    }
}