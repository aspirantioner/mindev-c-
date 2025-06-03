#ifndef SIGNATUREFIELD_H_
#define SIGNATUREFIELD_H_

#include "signaturecontainer.h"

namespace mindev::component{
    class SignatureField{
public:
    SignatureField(){}
    SignatureField(const SignatureContainer& container){this->signatures = container;}
    inline void AddSignature(const Signature& signature){this->signatures.AddElement(signature);}
    inline SignatureContainer& GetSignatures(){return this->signatures;}
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    SignatureContainer signatures;
    };
}

#endif
