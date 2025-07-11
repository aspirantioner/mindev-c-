#ifndef VMSTYPE_H_
#define VMSTYPE_H_

#include <string>
#include "mindev/include/common/uuid.hpp"
#include "mindev/include/packet/interest.h"

namespace mindev::logicface{
    class VmsType{
public:
        static const int VMS = 0;
        static const int VMS_MIS_Slice = 1;
        static const int VMS_MIS_1 = 2;
        static const int VMS_MIS_2 = 3;
        static const int MIS = 4;
        inline static std::string GetIdentifier(int method){
            static const int uuid_len = 32;
            std::string res = "";
            switch(method){
                case VMS:
                    res = "/vms/"+uuid::GenerateHexUUid(uuid_len);
                    break;
                case MIS:
                    res = "/mis/"+uuid::GenerateHexUUid(uuid_len);
                    break;
                default:
                    res = "/default";
            }
            return res;
        }
        inline static mindev::packet::Interest GetInterestForProxy(const std::string& identifier,const std::vector<char>& payload){
            static long ttl_value = 1234;
            static long nonce_value = 1234;
            static bool can_beprefix = true;
            mindev::packet::Interest interest;
            interest.SetNameByString(identifier);
            interest.payload.SetValue(payload);
            interest.ttl.SetTtl(ttl_value);
            interest.canBePrefix.SetCanBePrefix(can_beprefix);
            interest.nonce.SetNonce(nonce_value);
            return interest;
        }
        inline static mindev::packet::Interest GetInterestForSlice(const std::string& identifier,long slicenum){
            static long ttl_value = 1234;
            static long nonce_value = 1234;
            static bool can_beprefix = true;
            mindev::packet::Interest interest;
            interest.SetNameByString(identifier);
            interest.AppendFragmentNumber(slicenum);
            interest.ttl.SetTtl(ttl_value);
            interest.canBePrefix.SetCanBePrefix(can_beprefix);
            interest.nonce.SetNonce(nonce_value);
            return interest;
        }
    };
}

#endif