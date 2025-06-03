
#ifndef NONCE_H_
#define NONCE_H_

#include <random>

#include "tlvcomponentbase.h"
#include "initialable.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class Nonce:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
public:
    Nonce(){}
    Nonce(long nonce){this->SetNonce(nonce);this->doInitial();}
    inline long GetNonce(){return this->nonce;}
    inline void SetNonce(long nonce){this->nonce = nonce;this->doInitial();}
    inline void RefreshNonce(){
        long randomLong = GenerateRandomUnsignedLong();
        this->SetNonce(randomLong);
    }
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    uint64_t GenerateRandomUnsignedLong() {
        static std::random_device rd;
        static std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> dist(0, UINT64_MAX);
        return dist(gen);
    }
    long nonce;
    };
}

#endif
