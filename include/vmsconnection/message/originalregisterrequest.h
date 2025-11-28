#ifndef ORIGINAL_REGISTER_REQUEST_H_
#define ORIGINAL_REGISTER_REQUEST_H_

#include "common/json.hpp"
#include <string>
using json = nlohmann::json;
namespace mindev::vmsconnection::message {
    class OriginalRegisterRequest{
public:
    std::string username;
    std::string passwd;
    std::string phone_number;
    std::string email;
    std::string invite_number;
    OriginalRegisterRequest(const json& j){
        *this = j;
    };
    OriginalRegisterRequest(const std::string& username,const std::string& passwd,const std::string& phone_number,const std::string& email,const std::string& invite_number){
        this->username = username;
        this->passwd = passwd;
        this->phone_number = phone_number;
        this->email = email;
        this->invite_number = invite_number;
    }
    friend void to_json(json& j, const OriginalRegisterRequest& request);
    friend void from_json(const json& j, OriginalRegisterRequest& request);
    };
    void to_json(json& j, const OriginalRegisterRequest& request){
        j = json {
            {"username", request.username},  
            {"passwd", request.passwd},
            {"phoneNumber", request.phone_number},
            {"email",request.email},
            {"inviteNumber",request.invite_number}
        };
    }
    void from_json(const json& j, OriginalRegisterRequest& request){
        j.at("username").get_to(request.username);
        j.at("passwd").get_to(request.passwd);
        j.at("phoneNumber").get_to(request.phone_number);
        j.at("email").get_to(request.email);
        j.at("inviteNumber").get_to(request.invite_number);
    }
}
#endif