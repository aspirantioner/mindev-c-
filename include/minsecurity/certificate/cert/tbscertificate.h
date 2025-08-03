#ifndef TBSCERTIFICATE_H_
#define TBSCERTIFICATE_H_

#include "mindev/include/common/byteutils.h"
#include <vector>
#include <string>

namespace mindev::minsecurity::certificate::cert {
    class TbsCertificate {
public:
    TbsCertificate(){}
    TbsCertificate(int version, long serialNumber,
                       const std::vector<char>& publicKey, int signatureAlgorithm,
                       int publicKeyAlgorithm,
                       const std::string& issueTo, const std::string& issuer,
                       long notBefore, long notAfter,
                       int keyUsage, bool isCA, long timestamp) {
        this->version = version;
        this->serialNumber = serialNumber;
        this->publicKey = publicKey;
        this->signatureAlgorithm = signatureAlgorithm;
        this->publicKeyAlgorithm = publicKeyAlgorithm;
        this->issueTo = issueTo;
        this->issuer = issuer;
        this->notBefore = notBefore;
        this->notAfter = notAfter;
        this->keyUsage = keyUsage;
        this->isCA = isCA;
        this->timestamp = timestamp;
    }

    int GetVersion() {
        return version;
    }

    void SetVersion(int version) {
        this->version = version;
    }

    long GetSerialNumber() {
        return serialNumber;
    }

    void SetSerialNumber(long serialNumber) {
        this->serialNumber = serialNumber;
    }

    int GetSignatureAlgorithm() {
        return signatureAlgorithm;
    }

    void SetSignatureAlgorithm(int signatureAlgorithm) {
        this->signatureAlgorithm = signatureAlgorithm;
    }

    int GetPublicKeyAlgorithm() {
        return publicKeyAlgorithm;
    }

    void SetPublicKeyAlgorithm(int publicKeyAlgorithm) {
        this->publicKeyAlgorithm = publicKeyAlgorithm;
    }

    std::string getIssueTo() {
        return issueTo;
    }
    
    void SetIssueTo(const std::string& issueTo) {
        this->issueTo = issueTo;
    }

    std::string GetIssuer() {
        return issuer;
    }

    void SetIssuer(const std::string& issuer) {
        this->issuer = issuer;
    }
    
    long GetNotBefore() const {
        return notBefore;
    }
    
    void SetNotBefore(long notBefore) {
        this->notBefore = notBefore;
    }

    long GetNotAfter() const {
        return notAfter;
    }

    void SetNotAfter(long notAfter) {
        this->notAfter = notAfter;
    }

    int GetKeyUsage() {
        return keyUsage;
    }

    void SetKeyUsage(int keyUsage) {
        this->keyUsage = keyUsage;
    }

    bool IsCA() {
        return isCA;
    }

    void SetCA(bool CA) {
        isCA = CA;
    }

    long GetTimestamp() {
        return timestamp;
    }

    void SetTimestamp(long timestamp) {
        this->timestamp = timestamp;
    }

    std::vector<char>& GetPublicKey() {
        return publicKey;
    }

    void SetPublicKey(const std::vector<char>& publicKey) {
        this->publicKey = publicKey;
    }

    std::string ToString() {
        std::string ans = "";
        return ans+"TbsCertificate{" +
                "version=" + std::to_string(version) +
                ", serialNumber=" + std::to_string(serialNumber) +
                ", publicKey=" + (publicKey.size()==0?"":byteutils::VectorToHex(publicKey)) +
                ", signatureAlgorithm=" + std::to_string(signatureAlgorithm) +
                ", publicKeyAlgorithm=" + std::to_string(publicKeyAlgorithm) +
                ", issueTo='" + issueTo + '\'' +
                ", issuer='" + issuer + '\'' +
                ", notBefore=" + std::to_string(notBefore) +
                ", notAfter=" + std::to_string(notAfter) +
                ", keyUsage=" + std::to_string(keyUsage) +
                ", isCA=" + std::to_string(int(isCA)) +
                ", timestamp=" + std::to_string(timestamp) +
                '}';
    }
private:
    int version;
    long serialNumber;
    std::vector<char> publicKey;
    int signatureAlgorithm;
    int publicKeyAlgorithm;
    std::string issueTo;
    std::string issuer;
    long notBefore;
    long notAfter;
    int keyUsage;
    bool isCA;
    long timestamp;
    };
}


#endif