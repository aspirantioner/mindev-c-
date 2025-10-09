#ifndef CERTIFICATE_H_
#define CERTIFICATE_H_

#include "mindev/include/minsecurity/crypto/publickeyinterface.h"
#include "mindev/include/common/byteutils.h"
#include <vector>
#include <string>

namespace mindev::minsecurity::certificate::cert {
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

    int GetVersion() const{
        return version;
    }
    
    bool IsEmpty()const{
        return version == -1;
    }

    void SetVersion(int version) {
        this->version = version;
    }

    long GetSerialNumber() const{
        return serialNumber;
    }

    void SetSerialNumber(long serialNumber) {
        this->serialNumber = serialNumber;
    }


    std::vector<char> GetSignature() const{
        return signature;
    }

    void SetSignature(const std::vector<char>& signature) {
        this->signature = signature;
    }

    int GetSignatureAlgorithm() const{
        return signatureAlgorithm;
    }

    void SetSignatureAlgorithm(int signatureAlgorithm) {
        this->signatureAlgorithm = signatureAlgorithm;
    }

    int GetPublicKeyAlgorithm() const{
        return publicKeyAlgorithm;
    }

    void SetPublicKeyAlgorithm(int publicKeyAlgorithm) {
        this->publicKeyAlgorithm = publicKeyAlgorithm;
    }

    std::string getIssueTo() const{
        return issueTo;
    }
    
    void SetIssueTo(const std::string& issueTo) {
        this->issueTo = issueTo;
    }

    std::string GetIssuer() const{
        return issuer;
    }

    void SetIssuer(const std::string& issuer) {
        this->issuer = issuer;
    }
    
    long GetNotBefore() const{
        return notBefore;
    }
    
    void SetNotBefore(long notBefore) {
        this->notBefore = notBefore;
    }

    long GetNotAfter() const{
        return notAfter;
    }

    void SetNotAfter(long notAfter) {
        this->notAfter = notAfter;
    }

    int GetKeyUsage() const{
        return keyUsage;
    }

    void SetKeyUsage(int keyUsage) {
        this->keyUsage = keyUsage;
    }

    bool IsCA() const {
        return isCA;
    }

    void SetCA(bool CA) {
        isCA = CA;
    }

    long GetTimestamp() const{
        return timestamp;
    }

    void SetTimestamp(long timestamp) {
        this->timestamp = timestamp;
    }

    const minsecurity::crypto::PublicKeyInterface& GetPublicKey() const{
        return publicKey;
    }

    void SetPublicKey(const mindev::minsecurity::crypto::PublicKeyInterface& publicKey) {
        this->publicKey = publicKey;
    }
    bool IsValid() const{
        return GetPublicKey().GetBytes().size() != 0;
    }
    std::string ToString() const{
        std::string ans = "";
        return ans+"Certificate{" +
                "version=" + std::to_string(version) +
                ", serialNumber=" + std::to_string(serialNumber) +
                ", publicKey=" + byteutils::VectorToHex(publicKey.GetBytes()) +
                ", signature=" + (signature.size()!=0 ? byteutils::VectorToHex(signature) : "null") +
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
    int version = -1;
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