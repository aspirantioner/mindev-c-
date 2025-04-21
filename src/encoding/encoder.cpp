#include "mindev/include/encoding/encoder.h"

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
}