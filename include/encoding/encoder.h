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
private:
    int left;
    int right;
    bool isEstimator;
    SizeT totalReserve;
    
    };
}
#endif