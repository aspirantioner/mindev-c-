#ifndef ENCODER_H_
#define ENCODER_H_

#include <vector>
#include "sizet.h"

namespace mindev::encoding {
    class Encoder{
public:
    static const int MaxPacketSize = 8000;
    std::vector<char> buffer;
    bool isInitial;
    void EstimatorReset();
    bool EncoderReset(const SizeT& totalReverse,const SizeT& reserveFromBack);
    inline bool Empty()const{return this->left+1>=this->right;}
    inline SizeT Size()const{return SizeT(this->right-this->left-1);}
    bool Check(const SizeT& size);
    int PrependByte(char value);
    int AppendByte(char value);
private:
    int left;
    int right;
    bool isEstimator;
    SizeT totalReserve;
    
    };
}
#endif