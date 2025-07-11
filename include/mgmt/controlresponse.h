#ifndef CONTROLRESPONSE_H_
#define CONTROLRESPONSE_H_

#include <string>
#include <variant>
#include "mindev/include/common/json.hpp"
#include "mindev/include/mgmt/controlresponsemeta.h"

namespace mindev::mgmt {
    class ControlResponse{
public:
    // 请求成功
    static const int ControlResponseCodeSuccess=200;
    // 请求到元数据，实际数据较大，已经分片，需要发起多个请求拉取分片
    static const int ControlResponseCodeContinue=201;
    // 请求错误，包含错误信息
    static const int ControlResponseCodeCommonError=400;

    // Data 域格式
    // string类型
    inline static const std::string ControlResponseTypeString = "string";
    // 元数据类型
    inline static const std::string ControlResponseTypeMeta   = "meta";
    // 字节数组类型
    inline static const std::string ControlResponseTypeBytes  = "bytes";
    std::string type;
    int code;
    std::string msg;
    std::variant<std::string,std::vector<char>,ControlResponseMeta> data;
    ControlResponse(){};
    ControlResponse(const ControlResponse& response){
        this->type = response.type;
        this->msg = response.msg;
        this->code = response.code;
        this->data = response.data;
    }
    inline std::string GetString(){
        if(std::holds_alternative<std::string>(this->data)){
            return std::get<std::string>(this->data);
        }
        return std::string();
    }
    inline void SetString(const std::string& str){
        this->data = str;
        this->type = ControlResponseTypeString;
    }
    inline std::vector<char> GetBytes(){
        if(std::holds_alternative<std::vector<char>>(this->data)){
            return std::get<std::vector<char>>(this->data);
        }
        return std::vector<char>();
    }
    inline void SetBytes(const std::vector<char>& bytes){
        this->data = bytes;
        this->type = ControlResponseTypeBytes;
    }
    inline ControlResponseMeta GetMeta(){
        if(std::holds_alternative<ControlResponseMeta>(this->data)){
            return std::get<ControlResponseMeta>(this->data);
        }
        return ControlResponseMeta();
    }
    inline void SetMeta(const ControlResponseMeta& meta){
        this->data = meta;
        this->type = ControlResponseTypeMeta;
    }
    bool UnmarshalJSON(const std::string& json_str);
    };
}

#endif