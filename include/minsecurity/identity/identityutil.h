#ifndef IDENTITYUTIL_H_
#define IDENTITYUTIL_H_

#include "mindev/include/minsecurity/identity/db.h"
#include "mindev/include/minsecurity/certificate/cert/certutils.h"
#include "mindev/include/minsecurity/common.h"
#include "mindev/include/minsecurity/crypto/sm2/sm2keypair.hpp"
#include "mindev/include/minsecurity/identity/identity.h"
#include "mindev/include/minsecurity/identity/inneridentity.h"
#include <cstdint>
#include <optional>
namespace mindev::minsecurity::identity {

    class IdentityUtil{
public:
    
    static std::optional<InnerIdentity> ParseIdentityToInner(const mindev::minsecurity::identity::Identity& identity){
        if(identity.GetPubKey().GetBytes().size() == 0 || identity.GetPriKey().GetBytes().size() == 0 || (haveUsedCert && !identity.GetCert().IsValid())){
            return std::nullopt;
        }
        InnerIdentity innerIdentity;
        innerIdentity.SetName(identity.GetName());
        innerIdentity.SetKeyParam(identity.GetKeyParam());
        innerIdentity.SetPrikey(identity.GetPriKey().GetBytes());
        innerIdentity.SetPubkey(identity.GetPubKey().GetBytes());
        innerIdentity.SetPasswd(identity.GetPasswd());
        if constexpr (haveUsedCert){
            innerIdentity.SetCert(mindev::minsecurity::certificate::cert::CertUtils::ToPem(identity.GetCert(),byteutils::StringToVector<uint8_t>(identity.GetPasswd()),(int)mindev::minsecurity::Common::SymmetricAlgorithm::SM4CBC));
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
        auto sm2_pair = crypto::sm2::SM2KeyPair::GenerateKeyPair();
        sm2_pair.GetSm2PublicKey().SetBytes(byteutils::CharToUint8(innerIdentity.GetPubKey()));
        sm2_pair.GetSm2PrivateKey().SetBytes(byteutils::CharToUint8(innerIdentity.GetPriKey()));
        identity.SetPubkey(sm2_pair.GetSm2PublicKey());
        identity.SetPrikey(sm2_pair.GetSm2PrivateKey());
        identity.SetPasswd(innerIdentity.GetPasswd());
        if constexpr(haveUsedCert){
            certificate::cert::Certificate certificate = certificate::cert::CertUtils::FromPem(innerIdentity.GetCert(),byteutils::StringToVector<uint8_t>(innerIdentity.GetPasswd()),(int)minsecurity::Common::SymmetricAlgorithm::SM4CBC);
            identity.SetCert(certificate);
        }
        identity.SetPrikeyRawByte(innerIdentity.GetPrikeyRawByte());
        return identity;
    }
    static std::optional<Identity> FromIdentityInfo(const struct IdentityInfo& info){
        Identity identity;
        identity.SetName(info.name);
        auto sm2_pair = crypto::sm2::SM2KeyPair::GenerateKeyPair();
        sm2_pair.GetSm2PublicKey().SetBytes(byteutils::StringToVector<uint8_t>(info.pubkey));
        sm2_pair.GetSm2PrivateKey().SetBytes(byteutils::StringToVector<uint8_t>(info.prikey));
        identity.SetPubkey(sm2_pair.GetSm2PublicKey());
        identity.SetPrikey(sm2_pair.GetSm2PrivateKey());
        identity.SetKeyParam(mindev::minsecurity::identity::KeyParam(info.pubkey_algo, info.signature_algo));
        identity.SetDefault(info.is_default);
        identity.SetPasswd(info.pass);
        certificate::cert::Certificate certificate = certificate::cert::CertUtils::FromPem(info.cert,byteutils::StringToVector<uint8_t>(info.pass), (int)minsecurity::Common::SymmetricAlgorithm::SM4CBC);
        identity.SetCert(certificate);
        return identity;
    }
private:
    const static bool haveUsedCert = false;
    
    };
}
#endif