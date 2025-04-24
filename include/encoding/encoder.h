#ifndef ENCODER_H_
#define ENCODER_H_

#include <vector>
#include "mindev/include/encoding/elementcontainer.h"
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
    static std::vector<char> BuildNonNegativeIntegerArr(long uint64_value);
    int PrependByteArray(std::vector<char>& array,const SizeT& size);
    int AppendByteArray(std::vector<char>& array,const SizeT& size);
    int AppendNonNegativeInteger(long uint64_value);
    int PrependVarNumber(const VlInt& varNumber);
    int AppendVarNumber(const VlInt& varNumber);
    int PrependByteArrayBlock(const VlInt& tlvType, std::vector<char>& array,const SizeT& size);
    int AppendByteArrayBlock(const VlInt& tlvType, std::vector<char>& array,const SizeT& size);
    int PrependBlock(Block& block);
    int AppendBlock(Block& block);
    std::vector<char> GetBuffer() const;
private:
    int left;
    int right;
    bool isEstimator;
    SizeT totalReserve;
    
    };
}
#endif