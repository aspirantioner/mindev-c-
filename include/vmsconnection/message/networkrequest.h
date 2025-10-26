#ifndef NETWORK_REQUEST_H_
#define NETWORK_REQUEST_H_
#include <cstdint>
#include <string>
#include "mindev/include/common/json.hpp"
using json = nlohmann::json;
namespace mindev::vmsconnection::message {
    class NetworkRequest{
public:
    std::string method;
    std::string type;
    std::string command;
    json header;
    std::vector<uint8_t> parameters;
    NetworkRequest(const std::string& type,const std::string& command,const std::vector<uint8_t>& parameters){
        this->type = type;
        this->command = command;
        this->parameters = parameters;
    }
    friend void to_json(json& j, const NetworkRequest& request);
    friend void from_json(const json& j, NetworkRequest& request);
    };
    void to_json(json& j, const NetworkRequest& request){
        j = json {
            {"Method", request.method},  
            {"Type", request.type},
            {"Command", request.command},
            {"Header",request.header},
            {"Parameters",request.parameters}
        };
    }
    void from_json(const json& j, NetworkRequest& request){
        j.at("Method").get_to(request.method);
        j.at("Type").get_to(request.type);
        j.at("Command").get_to(request.command);
        j.at("Header").get_to(request.header);
        j.at("Parameters").get_to(request.parameters);
    }
}
#endif