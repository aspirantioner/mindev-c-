#ifndef SM2KEYPAIR_H_
#define SM2KEYPAIR_H_

#include "mindev/include/minsecurity/crypto/sm2/sm2privatekey.h"
#include "mindev/include/minsecurity/crypto/sm2/sm2publickey.h"
namespace mindev::minsecurity::crypto::sm2 {
    class SM2KeyPair{
public:
    SM2KeyPair(const SM2PublicKey& sm2publickey,const SM2PrivateKey& sm2privatekey){
        this->sm2publickey = sm2publickey;
        this->sm2privatekey = sm2privatekey;
    }
    static SM2KeyPair GenerateKeyPair(){
        gm_bn_t k;
        gm_point_t p;
        gm_sm2_gen_keypair(k, &p);
        return SM2KeyPair(SM2PublicKey(p),SM2PrivateKey(k));
    }
    SM2PublicKey& GetSm2PublicKey(){
        return this->sm2publickey;
    }
    SM2PrivateKey& GetSm2PrivateKey(){
        return this->sm2privatekey;
    }
private:
    mindev::minsecurity::crypto::sm2::SM2PublicKey sm2publickey;
    mindev::minsecurity::crypto::sm2::SM2PrivateKey sm2privatekey;
    };

}

#endif