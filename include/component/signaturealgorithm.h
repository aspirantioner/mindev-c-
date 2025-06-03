#ifndef SIGNATUREALGORITHM_H_
#define SIGNATUREALGORITHM_H_

#include <memory>
namespace mindev::component{
    class SignatureAlgorithm{
    private:
        int signatureAlgorithm;
    public:
        typedef std::shared_ptr<SignatureAlgorithm> ptr;
        SignatureAlgorithm(){}
        SignatureAlgorithm(int value){this->SetSignatureAlgorithm(value);}
        inline int GetSignatureAlgorithm(){return this->signatureAlgorithm;}
        inline void SetSignatureAlgorithm(int value){this->signatureAlgorithm = value;}
    };
}

#endif
