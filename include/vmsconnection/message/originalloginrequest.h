#ifndef ORIGINAL_LOGIN_REQUEST_H_
#define ORIGINAL_LOGIN_REQUEST_H_

#include <string>
namespace mindev::vmsconnection::message {
    class OriginalLoginRequest{
public:
    std::string username;
    std::string passwd;
    OriginalLoginRequest(const std::string& username,const std::string& passwd){
        this->username = username;
        this->passwd = passwd;
    }
    };
}
#endif