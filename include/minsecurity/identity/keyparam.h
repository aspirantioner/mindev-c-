#ifndef KEYPARAM_H_
#define KEYPARAM_H_

#include "mindev/include/common/json.hpp"
using json = nlohmann::json;
namespace mindev::minsecurity::identity {

class KeyParam{
public:
    int PublicKeyAlgorithm;
   
    int SignatureAlgorithm;

     KeyParam(int publicKeyAlgorithm, int signatureAlgorithm) {
        this->PublicKeyAlgorithm = publicKeyAlgorithm;
        this->SignatureAlgorithm = signatureAlgorithm;
    }

    KeyParam() {}
    friend void to_json(json& j, const KeyParam& keyparam);
    friend void from_json(const json& j, KeyParam& keyparam);
};

inline void to_json(json& j, const KeyParam& keyparam) {
    j = json{
        {"PublicKeyAlgorithm", keyparam.PublicKeyAlgorithm},  
        {"SignatureAlgorithm", keyparam.SignatureAlgorithm},
    };
}

inline void from_json(const json& j,KeyParam& keyparam) {
    j.at("PublicKeyAlgorithm").get_to(keyparam.PublicKeyAlgorithm);
    j.at("SignatureAlgorithm").get_to(keyparam.SignatureAlgorithm);
}
}
#endif