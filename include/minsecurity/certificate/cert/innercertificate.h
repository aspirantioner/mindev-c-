#ifndef INNERCERTIFICATE_H_
#define INNERCERTIFICATE_H_

#include "mindev/include/common/byteutils.h"
#include "mindev/include/minsecurity/certificate/cert/tbscertificate.h"
#include <vector>
#include <string>

namespace mindev::minsecurity::certificate::cert {
    class InnerCertificate {
public:
    InnerCertificate(){}

    const TbsCertificate& GetTbsCertificate() const{
        return tbsCertificate;
    }

    void SetTbsCertificate(const TbsCertificate& tbsCertificate) {
        this->tbsCertificate = tbsCertificate;
    }
    

    int GetSignatureAlgorithm() const{
        return signatureAlgorithm;
    }

    void SetSignatureAlgorithm(int signatureAlgorithm) {
        this->signatureAlgorithm = signatureAlgorithm;
    }

    

    const std::vector<char>& GetSignatureValue() const{
        return this->signatureValue;
    }

    void SetSignatureValue(const std::vector<char>& signatureValue) {
        this->signatureValue = signatureValue;
    }

    std::string ToString() {
        std::string ans = "";
        return ans+"InnerCertificate{" +
                "tbscertificate="+tbsCertificate.ToString()+
                ", signatureAlgorithm="+ std::to_string(signatureAlgorithm)+
                ", signatureValue"+(signatureValue.size()==0?"null":byteutils::VectorToHex(signatureValue))+
                "}";
    }
private:
    TbsCertificate tbsCertificate;
    int signatureAlgorithm;
    std::vector<char> signatureValue;
    };
}


#endif