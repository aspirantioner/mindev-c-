#ifndef SIGNATURE_H_
#define SIGNATURE_H_

#include "signatureinfo.h"
#include "signaturevalue.h"
namespace mindev::component{
    class Signature{
private:
    SignatureInfo::ptr sigInfo=std::make_shared<SignatureInfo>();
    SignatureValue::ptr sigValue=std::make_shared<SignatureValue>();
    };
}

#endif
