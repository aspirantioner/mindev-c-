#ifndef NACKHEADER_H_
#define NACKHEADER_H_

#include "mindev/include/component/initialable.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class NackHeader:public TlvComponentBase,public mindev::encoding::IEncodingAble,public InitialAble{
private:
    long nackReason;
public:
    static const long NackReasonUnkown = 0;
    static const long NackReasonDuplicate = 1;
    static const long NackReasonNoRoute = 2;
    NackHeader(){};
    NackHeader(long nackReason){this->SetNackReason(nackReason);this->doInitial();}
    inline long  GetNackReason(){return this->nackReason;}
    inline void SetNackReason(long nackReason){this->nackReason = nackReason;}
    static std::string GetNackReasonString(long reason){
        switch(reason){
            case NackReasonUnkown:
                return "Unknown";
            case NackReasonDuplicate:
                return "Duplicate";
            case NackReasonNoRoute:
                return "NoRoute";
        }
        return "Unknown";
    } 
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
