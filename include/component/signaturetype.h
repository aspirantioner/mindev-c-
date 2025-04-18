
#ifndef SIGNATURETYPE_H_
#define SIGNATURETYPE_H_

#include "signaturealgorithm.h"

namespace mindev::component{
    class SignatureType{
private:
    SignatureAlgorithm::ptr value=std::make_shared<SignatureAlgorithm>(); // SignatureAlgorithm

public: 
    
    typedef std::shared_ptr<SignatureType> ptr;
    SignatureType(){}
    };
}

#endif
