#ifndef CERTUTILS_H_
#define CERTUTILS_H_

#include "mindev/include/common/base64.hpp"
#include "mindev/include/common/json.hpp"
#include "mindev/include/minsecurity/certificate/cert/certificate.h"
#include "mindev/include/minsecurity/certificate/cert/innercertificate.h"
#include "mindev/include/minsecurity/common.h"
#include "mindev/include/minsecurity/crypto/keyutils.h"
#include "mindev/include/minsecurity/crypto/privatekeyinterface.h"
#include "mindev/include/common/timeutils.h"
#include "mindev/include/minsecurity/crypto/sm4.h"
#include <cstdint>

namespace mindev::minsecurity::certificate::cert {
    class CertUtils{
public:
    static const int version = 1;
    static InnerCertificate ParseCertToInnerCert(const Certificate& certificate);
    static Certificate ParseInnerCertToCert(const InnerCertificate&  innercert);
    static bool CheckDuration(const InnerCertificate& innerCertificate){
        auto curTime = timeutils::GetCurrentTime();
        return innerCertificate.GetTbsCertificate().GetNotAfter() >= curTime && innerCertificate.GetTbsCertificate().GetNotBefore() <= curTime;
    }
    template<typename Object>
    static std::vector<char> Serialization(const Object& object){
        json j = object;
        auto j_str = j.dump();
        return std::vector<char>(j_str.begin(),j_str.end());
    }
    template<typename Object>
    static Object DeSerialization(const std::vector<uint8_t>& vec){
        auto j = json::parse(vec.begin(),vec.end());
        return j.get<Object>();
    }
    static bool CheckSign(const InnerCertificate& innerCertificate,const crypto::PublicKeyInterface& publicKey){
        switch (innerCertificate.GetTbsCertificate().GetSignatureAlgorithm()){
            case (int)mindev::minsecurity::Common::SignatureAlgorithm::SM3withSM2:
                auto cert_vec = Serialization(innerCertificate.GetTbsCertificate());
                return publicKey.Verify(cert_vec, innerCertificate.GetSignatureValue());
                break;
        }
        return false;
    }
    static void SignCert(Certificate& certificate,const crypto::PrivateKeyInterface& privatekey){
        auto cert_vec = Serialization(CertUtils::ParseCertToInnerCert(certificate).GetTbsCertificate());
        switch (certificate.GetSignatureAlgorithm()){
            case (int)mindev::minsecurity::Common::SignatureAlgorithm::SM3withSM2:
                certificate.SetSignature(privatekey.Sign(cert_vec));
                break;
        }
    }   
    static bool VerifyCert(const Certificate& ca,const Certificate& sub){
        auto innercertificate = CertUtils::ParseCertToInnerCert(ca);
        switch (innercertificate.GetTbsCertificate().GetVersion()){
            case CertUtils::version:
                bool isvalid = CertUtils::CheckDuration(innercertificate);
                if(!isvalid){
                    return false;
                }
                if(sub.IsCA()){
                    return CheckSign(innercertificate, sub.GetPublicKey());
                }else{
                    return CheckSign(innercertificate, ca.GetPublicKey());
                }
        }
        return false;
    }
    static std::string ToPem(const Certificate& certificate,const std::vector<uint8_t>& passwd,int symalgomode){
        std::string ret = "";
        if(certificate.IsEmpty() || !certificate.IsValid()){
            return ret;
        }
        if(certificate.GetSignature().size()==0){
            return ret;
        }
        auto cert_vec = Serialization(ParseCertToInnerCert(certificate));
        std::vector<uint8_t> uint8_vec(cert_vec.begin(),cert_vec.end());
        if(passwd.size()>0){
            auto sm4key = crypto::KeyUtils::Get16BytePasswd(passwd);
            switch (symalgomode){
                case (int)Common::SymmetricAlgorithm::SM4CBC:
                    ret = byteutils::VectorToString( mindev::minsecurity::crypto::SM4::EncryptCBCPadding(sm4key,byteutils::GenerateRandomVector<uint8_t>(SM4_BLOCK_SIZE),uint8_vec));
                    break;
                case (int)Common::SymmetricAlgorithm::SM4ECB:
                    ret = byteutils::VectorToString( mindev::minsecurity::crypto::SM4::EncryptECBPadding(sm4key,uint8_vec));
                    break;
            };
        }else{
            ret = byteutils::VectorToString(cert_vec);  
        }
        return Base64::Encode(ret);
    }
    static Certificate FromPem(const std::string& pemstring,const std::vector<uint8_t>& passwd,int symalgmode){
        
        if(pemstring.size()==0){
            return Certificate();
        }
        auto dec_pemstr = Base64::Decode(pemstring);
        std::vector<uint8_t> cert_vec = byteutils::StringToVector<uint8_t>(dec_pemstr);
        
        if(passwd.size()>0){
            auto sm4key = crypto::KeyUtils::Get16BytePasswd(passwd);
            switch (symalgmode){
                case (int)Common::SymmetricAlgorithm::SM4CBC:
                    cert_vec = mindev::minsecurity::crypto::SM4::DecryptCBCPadding(sm4key,byteutils::GenerateRandomVector<uint8_t>(SM4_BLOCK_SIZE),cert_vec);
                    break;
                case (int)Common::SymmetricAlgorithm::SM4ECB:
                    cert_vec = mindev::minsecurity::crypto::SM4::DecryptECBPadding(sm4key,cert_vec);
                    break;
            };
        }
        return ParseInnerCertToCert(DeSerialization<InnerCertificate>(cert_vec));
    }
    };
}

#endif