#ifndef TBSCERTIFICATE_H_
#define TBSCERTIFICATE_H_

#include "mindev/include/common/json.hpp"
#include "mindev/include/common/byteutils.h"
#include <vector>
#include <string>
using json = nlohmann::json;
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

    int GetVersion() const{
        return version;
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

    int GetKeyUsage() const{
        return keyUsage;
    }

    void SetKeyUsage(int keyUsage) {
        this->keyUsage = keyUsage;
    }

    bool IsCA() const{
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

    std::vector<char> GetPublicKey() const{
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
    
    friend void to_json(json& j,const TbsCertificate& cert);
    friend void from_json(const json& j, TbsCertificate& cert);
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
    // 序列化
    inline void to_json(json& j,const TbsCertificate& cert) {
        j = json{
            {"Version", cert.GetVersion()},
            {"SerialNumber", cert.GetSerialNumber()},
            {"PublicKey", cert.GetPublicKey()},
            {"SignatureAlgorithm", cert.GetSignatureAlgorithm()},
            {"PublicKeyAlgorithm", cert.GetPublicKeyAlgorithm()},
            {"IssueTo", cert.getIssueTo()},
            {"Issuer", cert.GetIssuer()},
            {"NotBefore", cert.GetNotBefore()},
            {"NotAfter", cert.GetNotAfter()},
            {"KeyUsage", cert.GetKeyUsage()},
            {"IsCA", cert.IsCA()},
            {"Timestamp", cert.GetTimestamp()}
        };
    }

    // 反序列化
    inline  void from_json(const json& j, TbsCertificate& cert) {
        j.at("Version").get_to(cert.version);
        j.at("SerialNumber").get_to(cert.serialNumber);
        j.at("PublicKey").get_to(cert.publicKey);
        j.at("SignatureAlgorithm").get_to(cert.signatureAlgorithm);
        j.at("PublicKeyAlgorithm").get_to(cert.publicKeyAlgorithm);
        j.at("IssueTo").get_to(cert.issueTo);
        j.at("Issuer").get_to(cert.issuer);
        j.at("NotBefore").get_to(cert.notBefore);
        j.at("NotAfter").get_to(cert.notAfter);
        j.at("KeyUsage").get_to(cert.keyUsage);
        j.at("IsCA").get_to(cert.isCA);
        j.at("Timestamp").get_to(cert.timestamp);
    }
}


#endif