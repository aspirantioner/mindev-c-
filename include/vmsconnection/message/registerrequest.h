#ifndef REGISTER_REQUEST_H_
#define REGISTER_REQUEST_H_
#include <cstdint>
#include <string>
#include "mindev/include/common/json.hpp"
using json = nlohmann::json;
namespace mindev::vmsconnection::message {
    class RegisterRequest{
public:
    int id;
    std::string name;
    std::string passwd;
    std::string phone;
    std::string invitation;
    std::string email;
    std::string deviceinfo;
    std::string certificate;
    int is_revoked;
    int ugroup_id;
    std::string timestamp;
    RegisterRequest(int id,const std::string& name,const std::string& passwd,const std::string& phone,const std::string& invitation,const std::string& email,const std::string& deviceinfo,const std::string& certification,int is_revoked,int ugroup_id,const std::string& timestamp){
        this->id = id;
        this->name = name;
        this->passwd = passwd;
        this->phone = phone;
        this->invitation = invitation;
        this->email = email;
        this->deviceinfo = deviceinfo;
        this->certificate = certification;
        this->is_revoked = is_revoked;
        this->ugroup_id = ugroup_id;
        this->timestamp = timestamp;
    }
    };
}
#endif