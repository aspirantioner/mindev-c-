#ifndef  DB_H_
#define  DB_H_

#include "mindev/include/common/json.hpp"
#include "mindev/include/minsecurity/crypto/hashalgo.h"
#include "mindev/include/minsecurity/crypto/keyutils.h"
#include "mindev/include/minsecurity/crypto/sm4.h"
#include "mindev/include/common/base64.hpp"
#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

using json = nlohmann::json;
namespace mindev::minsecurity::identity {
struct IdentityInfo {
    std::string name;
    std::string pubkey;
    std::string prikey;
    int pubkey_algo = 0;
    int signature_algo = 0;
    std::string pass;
    std::string cert;
    int is_default = 0;
    std::string prikey_raw_byte;
};

// json 序列化支持
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IdentityInfo,
    name, pubkey, prikey, pubkey_algo, signature_algo,
    pass, cert, is_default, prikey_raw_byte)

// void to_json(json& j, const IdentityInfo& info) {
//     j = json{
//         {"name", info.name},
//         {"pubKey", info.pubkey},
//         {"priKey", info.prikey},
//         {"pubkey_algo", info.pubkey_algo},
//         {"signature_algo", info.signature_algo},
//         {"pass", info.pass},
//         {"cert", info.cert},
//         {"is_default", info.is_default},
//         {"prikeyBytes", info.prikey_raw_byte}
//     };
// }
//
// void from_json(const json& j, IdentityInfo& info) {
//     j.at("name").get_to(info.name);
//     j.at("pubKey").get_to(info.pubkey);
//     j.at("priKey").get_to(info.prikey);
//     j.at("pubkey_algo").get_to(info.pubkey_algo);
//     j.at("signature_algo").get_to(info.signature_algo);
//     j.at("pass").get_to(info.pass);
//     j.at("cert").get_to(info.cert);
//     j.at("is_default").get_to(info.is_default);
//     j.at("prikeyBytes").get_to(info.prikey_raw_byte);
// }


class IdentityDatabase {
    public:
        using TableType = std::unordered_map<std::string, IdentityInfo>;
        
        // 加载数据
        bool Load(const std::string& filename,const std::string& passwd) {
            std::ifstream pass_in(passwd_digest_filename);
            if(!pass_in.is_open()) return false;
            std::ostringstream buf;
            buf << pass_in.rdbuf();
            passwd_digest.clear();
            passwd_digest.assign(buf.str().begin(), buf.str().end());
            if(passwd_digest.size()!=32){
                return false;
            }
            std::vector<uint8_t> passwd_vec(passwd.begin(),passwd.end());
            auto digest_res = mindev::minsecurity::crypto::HashAlgo::Sm3(passwd_vec);
//             passwd_vec.clear();
//             passwd_vec.assign(passwd_digest.begin(), passwd_digest.end());
            if(passwd_digest.size() != digest_res.size() || std::equal(passwd_digest.begin(), passwd_digest.end(), digest_res.begin())){
                return false;            
            };
            std::ifstream in(filename);
            if (!in.is_open()) return false;
            std::ostringstream enc_buf;
            enc_buf << in.rdbuf();
            std::string enc_str = enc_buf.str();
            std::vector<uint8_t> enc_vec(enc_str.begin(),enc_str.end());
            if(digest_res.size() == 32){
                for(int i = 0;i<16;i++){
                    digest_res[i] += digest_res[i+16];
                }
            }
            auto dec_vec = mindev::minsecurity::crypto::SM4::DecryptCBCPadding(digest_res,digest_res,enc_vec);
            std::string base64_str(dec_vec.begin(),dec_vec.end());
            auto plain_text = mindev::Base64::Decode(base64_str);
            json j = nlohmann::json::parse(plain_text.c_str());
            table_ = j.get<TableType>();
            return true;
        }
    
        // 保存数据
        bool Save(const std::string& filename = user_identity_filename) {
            std::ofstream out(filename);
            if (!out.is_open()) return false;
            
            json j = table_;
            auto plain_text = j.dump(4);
            plain_text = mindev::Base64::Encode(reinterpret_cast<const unsigned char*>(plain_text.c_str()), plain_text.size());
            auto digest = passwd_digest;
            if(digest.size() == 32){
                for(int i = 0;i<16;i++){
                    digest[i] += digest[i+16];
                }
            }
            std::vector<uint8_t> data_vec(plain_text.begin(),plain_text.end());
            auto enc_vec = mindev::minsecurity::crypto::SM4::EncryptCBCPadding(digest, digest, data_vec);
            out.write(reinterpret_cast<const char*>(enc_vec.data()), enc_vec.size());
            return true;
        }
    
        // 增
        bool Insert(const IdentityInfo& info) {
            if(table_.find(info.name)!=table_.end()){
                return false;
            }
            table_[info.name] = info;
            return true;
        }

        // 更
        bool Update(const IdentityInfo& info){
            if(table_.find(info.name)==table_.end()){
                return false;
            }
            table_[info.name] = info;
            return true;
        }
    
        // 查
        IdentityInfo* Find(const std::string& name) {
            auto it = table_.find(name);
            return (it != table_.end()) ? &it->second : nullptr;
        }
    
        // 删
        bool Erase(const std::string& name) {
            return table_.erase(name) > 0;
        }
    
    private:
        TableType table_;
        inline const static std::string user_identity_filename = "user_identity.db";
        inline const static std::string passwd_digest_filename = "passwd_digest.db";
        std::vector<uint8_t> passwd_digest;
};
}
#endif