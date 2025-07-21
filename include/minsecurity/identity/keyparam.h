#ifndef KEYPARAM_H_
#define KEYPARAM_H_

namespace mindev::minsecurity::identity {

class KeyParam{
public:
    int PublicKeyAlgorithm;
   
    int SignatureAlgorithm;

     KeyParam(int publicKeyAlgorithm, int signatureAlgorithm) {
        this->PublicKeyAlgorithm = publicKeyAlgorithm;
        this->SignatureAlgorithm = signatureAlgorithm;
    }

    KeyParam() {}
};

}
#endif