#ifndef TOKEN_REGISTER_REQUEST_H_
#define TOKEN_REGISTER_REQUEST_H_
#include <cstdint>
#include <string>
#include "mindev/include/common/json.hpp"
using json = nlohmann::json;
namespace mindev::vmsconnection::message {
    class TokenRegisterRequest{
public:
    int id;
    std::string name;
    std::string passwd;
    std::string phone;
    std::string invitation;
    std::string email;
    std::string deviceinfo;
    std::string certificate;
    std::string pubkey;
    int is_revoked;
    int ugroup_id;
    std::string timestamp;
    std::vector<uint8_t> encrypted_pwd;
    std::string token;
    TokenRegisterRequest(int id,const std::string& name,const std::string& passwd,const std::string& phone,const std::string& invitation,const std::string& email,const std::string& deviceinfo,const std::string& certification,const std::string& pubkey,int is_revoked,int ugroup_id,
    const std::string& timestamp,std::vector<uint8_t>& signature,const std::string& token){
        this->id = id;
        this->name = name;
        this->passwd = passwd;
        this->phone = phone;
        this->invitation = invitation;
        this->email = email;
        this->deviceinfo = deviceinfo;
        this->certificate = certification;
        this->pubkey = pubkey;
        this->is_revoked = is_revoked;
        this->ugroup_id = ugroup_id;
        this->timestamp = timestamp;
        this->encrypted_pwd = signature;
        this->token = token;
    }
    friend void to_json(json& j, const TokenRegisterRequest& request);
    friend void from_json(const json& j, TokenRegisterRequest& request);
    };
    inline void to_json(json& j, const TokenRegisterRequest& request) {
        j = json {
            {"ID", request.id},  
            {"Name", request.name},
            {"Password", request.passwd},
            {"Phone",request.phone},
            {"Invitation",request.invitation},
            {"Email",request.email},
            {"DeviceInfo",request.deviceinfo},
            {"Certificate",request.certificate},
            {"Pubkey",request.pubkey},
            {"IsRevoked",request.is_revoked},
            {"UGroupID",request.ugroup_id},
            {"TimeStamp",request.timestamp},
            {"EncryptedPwd",request.encrypted_pwd},
            {"token",request.token}
        };
    }
    
    inline void from_json(const json& j,TokenRegisterRequest& request) {
        j.at("ID").get_to(request.id);
        j.at("Name").get_to(request.name);
        j.at("Password").get_to(request.passwd);
        j.at("Phone").get_to(request.phone);
        j.at("Invitation").get_to(request.invitation);
        j.at("Email").get_to(request.email);
        j.at("DeviceInfo").get_to(request.deviceinfo);
        j.at("Certificate").get_to(request.certificate);
        j.at("Pubkey").get_to(request.pubkey);
        j.at("IsRevoked").get_to(request.is_revoked);
        j.at("UGroupID").get_to(request.ugroup_id);
        j.at("TimeStamp").get_to(request.timestamp);
        j.at("EncryptedPwd").get_to(request.encrypted_pwd);
        j.at("token").get_to(request.token);
    }
}
#endif