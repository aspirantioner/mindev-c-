#ifndef COMMON_H_
#define COMMON_H_

#include <string>

namespace mindev::security {
class Common {
public:
    // Algorithm Names
    inline static const std::string BC_NAME = "BC";
    inline static const std::string X509 = "X.509";
    inline static const std::string ALGO_NAME_EC = "EC";

    // Storage
    enum class Storage {
        SQLITE = 0
    };

    // PublicKeyAlgorithm
    enum class PublicKeyAlgorithm {
        SM2 = 0
    };

    // SignatureAlgorithm
    enum class SignatureAlgorithm {
        SM3withSM2 = 0
    };

    // SymmetricAlgorithm
    enum class SymmetricAlgorithm {
        SM4ECB = 0,
        SM4CBC = 1
    };

    // KeyUsage
    enum class KeyUsage {
        ContentCommitment = 0,
        DataEncipherment = 1,
        CertSign = 2
    };

    // TypeOfCert
    enum class TypeOfCert {
        InnerCertificate = 0,
        Certificate = 1,
        TbsCertificate = 2
    };
};
}
#endif