#ifndef SIGNATURE_H_
#define SIGNATURE_H_

#include "mindev/include/minsecurity/identity/identity.h"
#include "signatureinfo.h"
#include "signaturevalue.h"
#include <cstdint>

namespace mindev::component{
    class Signature{
public:
    Signature(){}
    Signature(const SignatureInfo& info,const SignatureValue& value){
        this->sigInfo = info;
        this->sigValue = value;
    }
    Signature(const mindev::minsecurity::identity::Identity& identity,std::vector<uint8_t>& value);
    inline SignatureValue& GetSigValue(){return this->sigValue;}
    inline SignatureInfo& GetSigInfo(){return this->sigInfo;}
private:
    SignatureInfo sigInfo;
    SignatureValue sigValue;
    };
}

#endif
