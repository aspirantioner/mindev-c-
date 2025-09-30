#include "mindev/include/minsecurity/certificate/cert/certutils.h"
#include "mindev/include/minsecurity/crypto/sm2/sm2keypair.h"

namespace mindev::minsecurity::certificate::cert {
    InnerCertificate CertUtils::ParseCertToInnerCert(const Certificate &certificate){
        TbsCertificate tbsCertificate;
        tbsCertificate.SetVersion(certificate.GetVersion());
        tbsCertificate.SetSerialNumber(certificate.GetSerialNumber());
        tbsCertificate.SetPublicKey(certificate.GetPublicKey().GetBytes());
        tbsCertificate.SetSignatureAlgorithm(certificate.GetSignatureAlgorithm());
        tbsCertificate.SetPublicKeyAlgorithm(certificate.GetPublicKeyAlgorithm());
        tbsCertificate.SetIssueTo(certificate.getIssueTo());
        tbsCertificate.SetIssuer(certificate.GetIssuer());
        tbsCertificate.SetNotAfter(certificate.GetNotAfter());
        tbsCertificate.SetNotBefore(certificate.GetNotBefore());
        tbsCertificate.SetKeyUsage(certificate.GetKeyUsage());
        tbsCertificate.SetCA(certificate.IsCA());
        tbsCertificate.SetTimestamp(certificate.GetTimestamp());
        
        InnerCertificate innercertificate;
        innercertificate.SetSignatureAlgorithm(certificate.GetSignatureAlgorithm());
        innercertificate.SetSignatureValue(certificate.GetSignature());
        innercertificate.SetTbsCertificate(tbsCertificate);
        return innercertificate;
    }
    Certificate CertUtils::ParseInnerCertToCert(const InnerCertificate&  innercert){
        Certificate certificate;
        auto tbscertificate = innercert.GetTbsCertificate();
        certificate.SetVersion(tbscertificate.GetVersion());
        certificate.SetSerialNumber(tbscertificate.GetSerialNumber());
        
        
        auto sm2_pair = crypto::sm2::SM2KeyPair::GenerateKeyPair();
        sm2_pair.GetSm2PublicKey().SetBytes(byteutils::CharToUint8(tbscertificate.GetPublicKey()));
        certificate.SetPublicKey(sm2_pair.GetSm2PublicKey());
        certificate.SetSignatureAlgorithm(tbscertificate.GetSignatureAlgorithm());
        certificate.SetPublicKeyAlgorithm(tbscertificate.GetPublicKeyAlgorithm());
        certificate.SetIssueTo(tbscertificate.getIssueTo());
        certificate.SetIssuer(tbscertificate.GetIssuer());
        certificate.SetNotAfter(tbscertificate.GetNotAfter());
        certificate.SetNotBefore(tbscertificate.GetNotBefore());
        certificate.SetKeyUsage(tbscertificate.GetKeyUsage());
        certificate.SetCA(tbscertificate.IsCA());
        certificate.SetTimestamp(tbscertificate.GetTimestamp());
    }
}