#ifndef PRIVATEKEYINTERFACE_H_
#define PRIVATEKEYINTERFACE_H_

#include <vector>
namespace mindev::minsecurity::crypto {
    class PublicKeyInterface {
public:
    virtual std::vector<char> GetBytes(){return std::vector<char>();}
    virtual bool SetBytes(const std::vector<char>& bytes){return true;}
    virtual std::vector<char> Encrypt(const std::vector<char>& content){return std::vector<char>();}
    bool Verify(const std::vector<char>& content,const std::vector<char>& digest){return true;}
    };
}


#endif