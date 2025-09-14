#ifndef KEYCHAIN_H_
#define KEYCHAIN_H_

#include "mindev/include/minsecurity/crypto/sm2/sm2keypair.h"
#include "mindev/include/minsecurity/identity/db.h"
#include "mindev/include/minsecurity/identity/identity.h"
#include "mindev/include/minsecurity/identity/keyparam.h"
#include <string>

namespace mindev::security {
class KeyChain {
public:
    bool Init(const std::string& passwd){
        if(!identity_db.Load(default_identity_dbpath,passwd)){
            return false;
        }
        auto ptr = identity_db.Find(default_identity_name);
        if(ptr==nullptr){
            auto sm2key_pair = minsecurity::crypto::sm2::SM2KeyPair::GenerateKeyPair();
            auto keyparam = mindev::minsecurity::identity::KeyParam((int)mindev::minsecurity::Common::PublicKeyAlgorithm::SM2,(int)mindev::minsecurity::Common::SignatureAlgorithm::SM3withSM2);
            minsecurity::identity::Identity new_identity = minsecurity::identity::Identity(default_identity_name,keyparam,sm2key_pair.GetSm2PrivateKey(),sm2key_pair.GetSm2PublicKey(),passwd,minsecurity::certificate::cert::Certificate(),false);
            if(passwd.size()!=0){
                new_identity.Lock(passwd,(int) mindev::minsecurity::Common::SymmetricAlgorithm::SM4ECB);
            }
            identity_db.Insert(new_identity.ToIdentityInfo());
            identity_db.Save();
            cur_identity = new_identity;
        }else{
            cur_identity = *ptr;
        }
        return true;
    }
    bool SetCurrentIdentity(minsecurity::identity::Identity& identity,const std::string& passwd){
        if(passwd.size() && identity.IsLocked()){
             if(!identity.UnLock(passwd,privateKeyEncryptionAlgorithm)){
                return false;
             }
        }
        cur_identity = identity;
        return true;
    }
    bool CheckIdentifyCanUseToSign(const mindev::minsecurity::identity::Identity& identity){
        return identity.HasPrivateKey() && !identity.IsLocked(); 
    }
    private:
        int privateKeyEncryptionAlgorithm = (int)minsecurity::Common::SymmetricAlgorithm::SM4ECB;
        inline static const std::string default_identity_name = "/localhost/operator";
        inline static const std::string default_identity_dbpath = "/usr/local/.mir/identity/";
        mindev::minsecurity::identity::IdentityDatabase identity_db;
        mindev::minsecurity::identity::Identity cur_identity;
};
}
#endif