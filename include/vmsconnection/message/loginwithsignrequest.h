#ifndef LOGINWITHSIGN_REQUEST_H_
#define LOGINWITHSIGN_REQUEST_H_

#include <cstdint>
#include <string>
#include "mindev/include/common/json.hpp"
using json = nlohmann::json;
namespace mindev::vmsconnection::message {
    class LoginWithSignRequest{
public:
    std::string name;
    std::string passwd;
    std::string certificate;
    std::vector<uint8_t> signature;
    std::string machineinfo;
    LoginWithSignRequest(const std::string& name,const std::string& passwd,const std::string& certificate,const std::vector<uint8_t>& signature,const std::string& machineinfo){
        this->name = name;
        this->passwd = passwd;
        this->certificate = certificate;
        this->signature = signature;
        this->machineinfo = machineinfo;
    }
    friend void to_json(json& j, const LoginWithSignRequest& request);
    friend void from_json(const json& j, LoginWithSignRequest& request);
    };
    void to_json(json& j, const LoginWithSignRequest& request){
        j = json {
            {"Name", request.name},  
            {"Password", request.passwd},
            {"Certificate", request.certificate},
            {"Signature", request.signature},
            {"MachineInfo", request.machineinfo}
        };
    }
    void from_json(const json& j, LoginWithSignRequest& request){
        j.at("Name").get_to(request.name);
        j.at("Password").get_to(request.passwd);
        j.at("Certificate").get_to(request.certificate);
        j.at("Signature").get_to(request.signature);
        j.at("MachineInfo").get_to(request.machineinfo);
    }
}
#endif