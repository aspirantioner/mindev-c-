#ifndef SIGNATURECONTAINER_H_
#define SIGNATURECONTAINER_H_

#include "signature.h"
#include <vector>

namespace mindev::component{
    class SignatureContainer{
public:
    SignatureContainer(){}
    inline int Length(){return this->signatures.size();}
    inline void Clear(){this->signatures.clear();}
    inline void AddElement(const Signature& signature){this->signatures.emplace_back(signature);}
    inline std::vector<Signature>& GetSignatures(){return this->signatures;}
    typedef std::shared_ptr<SignatureContainer> ptr;
private:
    std::vector<Signature> signatures;
    };
}

#endif
