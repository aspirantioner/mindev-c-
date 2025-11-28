#ifndef SIM_AUTH_REQUEST_H_
#define SIM_AUTH_REQUEST_H_

#include "common/json.hpp"
#include <string>

using json = nlohmann::json;
namespace mindev::vmsconnection::message {
    class SimAuthRequest{
public:
    std::string transactionId;
    SimAuthRequest(const std::string& transactionId){
        this->transactionId = transactionId;
    }
    friend void to_json(json& j, const SimAuthRequest& request);
    friend void from_json(const json& j, SimAuthRequest& request);
    };
    inline void to_json(json& j, const SimAuthRequest& request) {
        j = json {
            {"transactionId", request.transactionId}
        };
    }
    inline void from_json(const json& j,SimAuthRequest& request) {
        j.at("transactionId").get_to(request.transactionId);
    }
}
#endif