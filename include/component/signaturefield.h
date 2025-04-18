#ifndef SIGNATUREFIELD_H_
#define SIGNATUREFIELD_H_

#include "signaturecontainer.h"

namespace mindev::component{
    class SignatureField{
private:
    SignatureContainer::ptr signatures= std::make_shared<SignatureContainer>();
    };
}

#endif
