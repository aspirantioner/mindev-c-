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
        if (data.contains("data") && data["data"].is_object()) {
            if(this->type == ControlResponseTypeString){
                this->data = data["data"].get<std::string>();
            }else if (this->type == ControlResponseTypeBytes){
                this->data = data["data"].get<std::vector<char>>();
            }else if(this->type == ControlResponseTypeMeta){
                this->data = data["data"].get<ControlResponseMeta>();
            }else{
                return false;
            }
        } else {
            return false;
        }
        return true;
    }
}