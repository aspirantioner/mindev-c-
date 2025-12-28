#include "mindev/include/mgmt/controlresponse.h"

namespace mindev::mgmt {
    bool ControlResponse::UnmarshalJSON(const std::string& json_str){
        auto data = nlohmann::json::parse(json_str.c_str());
        if (data.contains("Type") && data["Type"].is_string()) {
            this->type = data["Type"].get<std::string>();
        } else {
            return false;
        }
        if (data.contains("Code") && data["Code"].is_number_integer()) {
            this->code = data["Code"].get<int>();
        } else {
            return false;
        }
        if (data.contains("Msg") && data["Msg"].is_string()) {
            this->msg = data["Msg"].get<std::string>();
        } else {
            return false;
        }
        if (data.contains("Data")) {
            if(this->type == ControlResponseTypeString && data["Data"].is_string()){
                this->data = data["Data"].get<std::string>();
            }else if (this->type == ControlResponseTypeBytes && data["Data"].is_array()){
                this->data = data["Data"].get<std::vector<char>>();
            }else if(this->type == ControlResponseTypeMeta && data["Data"].is_object()){
                this->data = data["Data"].get<ControlResponseMeta>();
            }else{
                return false;
            }
        } else {
            return false;
        }
        return true;
    }
}