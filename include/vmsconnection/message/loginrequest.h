#ifndef LOGIN_REQUEST_H_
#define LOGIN_REQUEST_H_

#include <string>
#include "mindev/include/common/json.hpp"
using json = nlohmann::json;
namespace mindev::vmsconnection::message {
    class LoginRequest{
public:
    std::string name;
    std::string passwd;
    std::string certificate;
    
    LoginRequest(const std::string& name,const std::string& passwd,const std::string& certificate){
        this->name = name;
        this->passwd = passwd;
        this->certificate = certificate;
    }
    friend void to_json(json& j, const LoginRequest& request);
    friend void from_json(const json& j, LoginRequest& request);
    }; 
    void to_json(json& j, const LoginRequest& request){
        j = json {
            {"Name", request.name},  
            {"Password", request.passwd},
            {"Certificate", request.certificate}
        };
    }
    void from_json(const json& j, LoginRequest& request){
        j.at("Name").get_to(request.name);
        j.at("Password").get_to(request.passwd);
        j.at("Certificate").get_to(request.certificate);
    }
}
#endif