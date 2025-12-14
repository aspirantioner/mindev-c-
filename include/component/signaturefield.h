#ifndef SIGNATUREFIELD_H_
#define SIGNATUREFIELD_H_

#include "signaturecontainer.h"

namespace mindev::component{
    class SignatureField:public mindev::encoding::IEncodingAble,public TlvComponentBase{
public:
    SignatureField(){}
    SignatureField(const SignatureContainer& container){this->signatures = container;}
    inline void AddSignature(const Signature& signature){this->signatures.AddElement(signature);}
    inline Signature GetSignature(int index){return signatures.GetSignatures().at(index);}
    inline SignatureContainer GetSignatures() const {return this->signatures;}
    inline void SetSignatures(const SignatureContainer& signatures){this->signatures=signatures;}
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
private:
    SignatureContainer signatures;
    };
}

#endif
