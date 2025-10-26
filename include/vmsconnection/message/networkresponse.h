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
    };
}
#endif