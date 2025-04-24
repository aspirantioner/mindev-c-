#include "mindev/include/encoding/encoder.h"
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
        if(reserveFromBack.GetVlIntValue()>totalReverve.GetVlIntValue()){
            return false;
        }    
        auto len = bigint::_bigint_to<int>(totalReverve.GetVlIntValue());
        if(len<=0){
            return false;
        }
        this->buffer.resize(len);
        this->right = bigint::_bigint_to<int>(totalReverve.GetVlIntValue() - reserveFromBack.GetVlIntValue());
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
        if(Check(size) && size<=array.size()){
            auto copy_len = bigint::_bigint_to<int>(size.GetVlIntValue());
            if(!this->isEstimator){
                std::copy(this->buffer.begin()+this->left-copy_len+1,this->buffer.begin()+this->left+1,array.begin());
            }
            this->left -= array.size();
            return copy_len;
        }
        return -1;
    }
    int Encoder::AppendByteArray(std::vector<char>& array,const SizeT& size){
        if(Check(size) && size<=array.size()){
            auto copy_len = bigint::_bigint_to<int>(size.GetVlIntValue());
            if(!this->isEstimator){
                std::copy(this->buffer.begin()+this->right,this->buffer.begin()+this->right+copy_len,array.begin());
            }
            this->right += array.size();
            return copy_len;
        }
        return -1;
    }
    int Encoder::AppendNonNegativeInteger(long uint64_value){
        auto bytes = BuildNonNegativeIntegerArr(uint64_value);
        return this->AppendByteArray(bytes,SizeT(bytes.size()));
        
    }
    int Encoder::PrependVarNumber(const VlInt& varNumber){
        auto temp = varNumber.GetVlIntBytes();
        return this->PrependByteArray(temp, SizeT(varNumber.GetSize()));
    }
    int Encoder::AppendVarNumber(const VlInt& varNumber){
        auto temp = varNumber.GetVlIntBytes();
        return this->AppendByteArray(temp, SizeT(varNumber.GetSize()));
    }
    int Encoder::PrependByteArrayBlock(const VlInt& tlvType,std::vector<char>& array,const SizeT& size){
        int totalLength = this->PrependByteArray(array, size);
        totalLength += this->PrependVarNumber(VlInt(size));
        totalLength += this->PrependVarNumber((tlvType));
        return totalLength;
    }
    int Encoder::AppendByteArrayBlock(const VlInt& tlvType,std::vector<char>& array,const SizeT& size){
        int totalLength =this->PrependVarNumber((tlvType)); 
        totalLength += this->PrependVarNumber(VlInt(size));
        totalLength += this->PrependByteArray(array, size);
        return totalLength;
    }
    int Encoder::PrependBlock(Block& block){
        auto temp = block.GetValue();
        return this->PrependByteArrayBlock(block.GetType(), temp, SizeT(block.GetLength()));
    }
    int Encoder::AppendBlock(Block& block){
        auto temp = block.GetValue();
        return this->AppendByteArrayBlock(block.GetType(), temp, SizeT(block.GetLength()));
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