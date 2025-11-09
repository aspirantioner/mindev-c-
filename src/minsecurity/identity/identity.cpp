#include "mindev/include/minsecurity/identity/identity.h"
#include "mindev/include/minsecurity/identity/identityutil.h"
#include <cstdint>
namespace mindev::minsecurity::identity {
    IdentityInfo Identity::ToIdentityInfo(){
        IdentityInfo res;
        res.name = Name;
        res.pubkey = byteutils::VectorToString(Pubkey.get()->GetBytes());
        res.prikey = byteutils::VectorToString(Prikey.get()->GetBytes());
        res.pubkey_algo = KeyParam.PublicKeyAlgorithm;
        res.signature_algo = KeyParam.SignatureAlgorithm;
        res.cert = certificate::cert::CertUtils::ToPem(Cert,std::vector<uint8_t>(),(int)mindev::minsecurity::Common::SymmetricAlgorithm::SM4ECB);
        res.prikey_raw_byte = byteutils::VectorToString(PrikeyRawByte);
        res.pass = GetPasswd();
        res.is_default = Isdefault();
        return res;
    }
    std::optional<Identity> Identity::Load(const std::vector<uint8_t>& serialbyte,const std::string& passwd){
        auto json_str = Base64::Decode(byteutils::VectorToString(serialbyte));
        if(passwd.size()>0){
            auto sm4key = crypto::KeyUtils::Get16BytePasswd(byteutils::StringToVector<uint8_t>(passwd));
            json_str = byteutils::VectorToString(minsecurity::crypto::SM4::DecryptCBCPadding(sm4key, byteutils::GenerateRandomVector<uint8_t>(16), byteutils::StringToVector<uint8_t>(json_str)));
        }
        auto j = json::parse(json_str.data());
        auto inneridentity = j.get<InnerIdentity>();
        return IdentityUtil::ParseInnerToIdentity(inneridentity);
    } 
    std::vector<uint8_t> Identity::Dump(const std::string& passwd)const{
        std::optional<InnerIdentity> inneridentity = IdentityUtil::ParseIdentityToInner(*this);
        if(!inneridentity.has_value()){
            return std::vector<uint8_t>();
        }
        json j = inneridentity.value();
        if(passwd.size()>0){
            auto sm4key = crypto::KeyUtils::Get16BytePasswd(byteutils::StringToVector<uint8_t>(passwd));
            auto cipher = minsecurity::crypto::SM4::EncryptCBCPadding(sm4key, byteutils::GenerateRandomVector<uint8_t>(16),byteutils::StringToVector<uint8_t>(j.dump()));
            return byteutils::StringToVector<uint8_t>(Base64::Encode(byteutils::VectorToString<uint8_t>(cipher)));
        }
        return byteutils::StringToVector<uint8_t>(Base64::Encode(j.dump()));
    }

    std::string Identity::DumpCert(const std::string& passwd){
        std::string res = "";
        if(!this->GetCert().IsValid()){
            return res;
        }
        if(this->GetCert().GetIssuer()=="" && this->GetCert().GetSignature().size()==0){
            return res;
        }
        return certificate::cert::CertUtils::ToPem(this->GetCert(),byteutils::StringToVector<uint8_t>(passwd) , (int)Common::SymmetricAlgorithm::SM4ECB);
    }
}