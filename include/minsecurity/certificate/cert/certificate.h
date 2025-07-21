#ifndef CERTIFICATE_H_
#define CERTIFICATE_H_

#include "mindev/include/minsecurity/crypto/publickeyinterface.h"
#include <vector>
#include <string>

namespace mindev::minsecurity::cert {
    class Certificate {
public:
    Certificate(){}
    Certificate(int version, long serialNumber,
                       const mindev::minsecurity::crypto::PublicKeyInterface& publicKey,
                       const std::vector<char>& signature, int signatureAlgorithm,
                       int publicKeyAlgorithm,
                       const std::string& issueTo,const std::string& issuer,
                       long notBefore, long notAfter,
                       int keyUsage, bool isCA, long timestamp) {
        this->version = version;
        this->serialNumber = serialNumber;
        this->publicKey = publicKey;
        this->signature = signature;
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


    std::vector<char>& GetSignature() {
        return signature;
    }

    void SetSignature(const std::vector<char>& signature) {
        this->signature = signature;
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
    
    long GetNotBefore() {
        return notBefore;
    }
    
    void SetNotBefore(long notBefore) {
        this->notBefore = notBefore;
    }

    long GetNotAfter() {
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

    minsecurity::crypto::PublicKeyInterface& GetPublicKey() {
        return publicKey;
    }

    void SetPublicKey(const mindev::minsecurity::crypto::PublicKeyInterface& publicKey) {
        this->publicKey = publicKey;
    }

    std::string ToString() {
        return "Certificate{" +
                "version=" + version +
                ", serialNumber=" + serialNumber +
                ", publicKey=" + publicKey +
                ", signature=" + (signature != nullptr ? ByteUtils.toHexString(signature) : "null") +
                ", signatureAlgorithm=" + signatureAlgorithm +
                ", publicKeyAlgorithm=" + publicKeyAlgorithm +
                ", issueTo='" + issueTo + '\'' +
                ", issuer='" + issuer + '\'' +
                ", notBefore=" + notBefore +
                ", notAfter=" + notAfter +
                ", keyUsage=" + keyUsage +
                ", isCA=" + isCA +
                ", timestamp=" + timestamp +
                '}';
    }
private:
    int version;
    long serialNumber;
    mindev::minsecurity::crypto::PublicKeyInterface publicKey;
    std::vector<char> signature;
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