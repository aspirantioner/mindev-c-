#ifndef SIGNATURE_H_
#define SIGNATURE_H_

#include "signatureinfo.h"
#include "signaturevalue.h"

namespace mindev::component{
    class Signature{
public:
    Signature(){}
    Signature(const SignatureInfo& info,const SignatureValue& value){
        this->sigInfo = info;
        this->sigValue = value;
    }
    inline SignatureValue& GetSigValue(){return this->sigValue;}
    inline SignatureInfo& GetSigInfo(){return this->sigInfo;}
private:
    SignatureInfo sigInfo;
    SignatureValue sigValue;
    };
}

#endif
