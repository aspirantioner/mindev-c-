
#ifndef SIGNATUREINFO_H_
#define SIGNATUREINFO_H_

#include "tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"
#include "signaturetype.h"
#include "keylocator.h"

namespace mindev::component{
    class SignatureInfo:public TlvComponentBase,public mindev::encoding::IEncodingAble {
public:    
    typedef std::shared_ptr<SignatureInfo> ptr;
    SignatureInfo(){}
private:
    SignatureType::ptr signatureType = std::make_shared<SignatureType>();
    KeyLocator::ptr keyLocator = std::make_shared<KeyLocator>();
    };
}

#endif
