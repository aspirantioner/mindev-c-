#ifndef NETWORK_RESPONSE_H_
#define NETWORK_RESPONSE_H_
#include <cstdint>
#include <string>
#include "mindev/include/common/json.hpp"
using json = nlohmann::json;
namespace mindev::vmsconnection::message {
    class NetworkResponse{
public:
    int code = 0;
    json header;
    std::vector<uint8_t> data;
    std::string errormsg;
    friend void to_json(json& j, const NetworkResponse& response);
    friend void from_json(const json& j, NetworkResponse& response);
    };
    void to_json(json& j, const NetworkResponse& response){
        j = json {
            {"Code", response.code},  
            {"Header", response.header},
            {"Data", response.data},
            {"ErrorMsg",response.errormsg}
        };
    }
    void from_json(const json& j, NetworkResponse& response){
        j.at("Code").get_to(response.code);
        j.at("Header").get_to(response.header);
        if(!j["Data"].is_null()){
            auto decode_str = mindev::Base64::Decode(j.at("Data"));
            response.data = byteutils::StringToVector<uint8_t>(decode_str);
        }
        j.at("ErrorMsg").get_to(response.errormsg);
    }
}
#endif