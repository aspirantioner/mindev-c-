#include "mindev/include/mgmt/controlresponse.h"

namespace mindev::mgmt {
    bool ControlResponse::UnmarshalJSON(const std::string& json_str){
        auto data = nlohmann::json::parse(json_str.c_str());
        if (data.contains("type") && data["type"].is_string()) {
            this->type = data["type"].get<std::string>();
        } else {
            return false;
        }
        if (data.contains("code") && data["code"].is_number_integer()) {
            this->code = data["code"].get<int>();
        } else {
            return false;
        }
        if (data.contains("msg") && data["msg"].is_string()) {
            this->msg = data["msg"].get<std::string>();
        } else {
            return false;
        }
        if (data.contains("data")) {
            if(data["data"].is_string()){
                this->data = data["data"].get<std::string>();
            }else if(data["data"].is_array()){
                this->data = data["data"].get<std::vector<char>>();
            }else if(data["data"].is_object()){
                if(data["data"].contains("Version") && data["data"].contains("SliceNum")  && data["data"]["Version"].is_number_integer() && data["data"]["SliceNum"].is_number_integer()){
                    ControlResponseMeta meta;
                    meta.Version = data["data"]["Version"].get<long>();
                    meta.SliceNum = data["data"]["Version"].get<long>();
                    this->data = meta;
                }
                else{
                    return false;
                }
            }else{
                return false;
            }
        } else {
            return false;
        }
        return true;
    }
}