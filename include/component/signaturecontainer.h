#ifndef SIGNATURECONTAINER_H_
#define SIGNATURECONTAINER_H_

#include "signature.h"
#include <list>

namespace mindev::component{
    class SignatureContainer{
public:
    typedef std::shared_ptr<SignatureContainer> ptr;
private:
    std::list<Signature> signatures;
    };
}

#endif
