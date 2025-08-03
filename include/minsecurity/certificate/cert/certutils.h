#ifndef CERTUTILS_H_
#define CERTUTILS_H_

#include "mindev/include/minsecurity/certificate/cert/certificate.h"
#include "mindev/include/minsecurity/certificate/cert/innercertificate.h"
#include "timeutils.h"

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
    
   
    };
}

#endif