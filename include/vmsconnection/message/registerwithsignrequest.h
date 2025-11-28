#ifndef REGISTERWITHSIGN_REQUEST_H_
#define REGISTERWITHSIGN_REQUEST_H_

#include <cstdint>
#include <string>
#include "mindev/include/common/json.hpp"
using json = nlohmann::json;
namespace mindev::vmsconnection::message {
    class RegisterWithSignRequest{
public:
    int id;
    std::string name;
    std::string passwd;
    std::string phone;
    std::string invitation;
    std::string email;
    std::string device_info;
    std::string certificate;
    std::string pubkey;
    int is_revoked;
    int ugroup_id;
    std::string timestamp;
    std::vector<uint8_t> encrypted_pwd;
    RegisterWithSignRequest(int id,const std::string& name,const std::string& passwd,const std::string& phone,const std::string& invitation,const std::string& email,const std::string& device_info,const std::string& certificate,const std::string& pubkey,int is_revoked,int ugroup_id,const std::string& timestamp,const std::vector<uint8_t>& encrypted_pwd){
        this->id = id;
        this->name = name;
        this->passwd = passwd;
        this->phone = phone;
        this->invitation = invitation;
        this->email = email;
        this->device_info = device_info;
        this->certificate = certificate;
        this->pubkey = pubkey;
        this->is_revoked = is_revoked;
        this->ugroup_id = ugroup_id;
        this->timestamp = timestamp;
        this->encrypted_pwd = encrypted_pwd;
    }
    friend void to_json(json& j, const RegisterWithSignRequest& request);
    friend void from_json(const json& j, RegisterWithSignRequest& request);
    };
    void to_json(json& j, const RegisterWithSignRequest& request){
        j = json {
            {"Name",request.name},
            {"Password",request.passwd},
            {"Phone",request.phone},
            {"Invitation",request.invitation},
            {"Email",request.email},
            {"DeviceInfo",request.device_info},
            {"Certificate",request.certificate},
            {"Pubkey",request.pubkey},
            {"IsRevoked",request.is_revoked},
            {"UGroupID",request.ugroup_id},
            {"TimeStamp",request.timestamp},
            {"EncryptedPwd",request.encrypted_pwd}
        };
    }
    void from_json(const json& j, RegisterWithSignRequest& request){
        j.at("Name").get_to(request.name);
        j.at("Password").get_to(request.passwd);
        j.at("Phone").get_to(request.phone);
        j.at("Invitation").get_to(request.invitation);
        j.at("Email").get_to(request.email);
        j.at("DeviceInfo").get_to(request.device_info);
        j.at("Certificate").get_to(request.certificate);
        j.at("Pubkey").get_to(request.pubkey);
        j.at("IsRevoked").get_to(request.is_revoked);
        j.at("UGroupID").get_to(request.ugroup_id);
        j.at("TimeStamp").get_to(request.timestamp);
        j.at("EncryptedPwd").get_to(request.encrypted_pwd);
    }
}
#endif