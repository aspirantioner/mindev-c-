
#ifndef PAYLOAD_H_
#define PAYLOAD_H_
#include "tlvcomponentbase.h"
#include "initialable.h"
#include "mindev/include/encoding/iencodingable.h"
#include <vector>
namespace mindev::component{
    class Payload:public TlvComponentBase,public InitialAble,public mindev::encoding::IEncodingAble{
public:
    Payload(){}
    Payload(const std::vector<char>& value){
        this->SetValue(value);
    }
    inline bool BuildPayloadBlock(mindev::encoding::Block& block){
        return this->WireDecode(block);
    } 
    inline std::vector<char> GetValue()const{return this->value;}
    inline void SetValue(const std::vector<char>& value){this->value = value;this->doInitial();}
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    std::vector<char> value;
    };
}

#endif
