#ifndef IDENTITYUTIL_H_
#define IDENTITYUTIL_H_

#include "mindev/include/minsecurity/certificate/cert/certutils.h"
#include "mindev/include/minsecurity/common.h"
#include "mindev/include/minsecurity/identity/identity.h"
#include "mindev/include/minsecurity/identity/inneridentity.h"
#include <optional>
namespace mindev::minsecurity::identity {

    class IdentityUtil{
public:
    static std::optional<InnerIdentity> ParseIdentityToInner(Identity& identity){
        if(identity.GetPubKey().GetBytes().size() == 0 || identity.GetPriKey().GetBytes().size() == 0 || identity.GetCert().GetPublicKey().GetBytes().size() == 0){
            return std::nullopt;
        }
        InnerIdentity innerIdentity;
        innerIdentity.SetName(identity.GetName());
        innerIdentity.SetKeyParam(identity.GetKeyParam());
        innerIdentity.SetPrikey(identity.GetPriKey().GetBytes());
        innerIdentity.SetPubkey(identity.GetPubKey().GetBytes());
        innerIdentity.SetPasswd(identity.GetPasswd());
        if constexpr (haveUsedCert){
            innerIdentity.SetCert(mindev::minsecurity::certificate::cert::CertUtils::ToPem(identity.GetCert(),identity.GetPasswd(),mindev::minsecurity::Common::SymmetricAlgorithm::SM4CBC));
        }
        innerIdentity.SetPrikeyRawByte(identity.GetPrikeyRawByte());
        return innerIdentity;
    }
    static std::optional<Identity> ParseInnerToIdentity(InnerIdentity& innerIdentity){
        Identity identity;
        if(innerIdentity.GetPubKey().size() == 0 || innerIdentity.GetPriKey().size() == 0){
            return std::nullopt;
        }
        identity.SetName(innerIdentity.GetName());
        identity.SetKeyParam(innerIdentity.GetKeyParam());
        
        identity.SetPasswd(innerIdentity.GetPasswd());
        identity.SetPrikeyRawByte(innerIdentity.GetPrikeyRawByte());
        return identity;
    }
private:
    const static bool haveUsedCert = false;
    
    };
}
#endif