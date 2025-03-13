#ifndef PUBLICKEY_H_
#define PUBLICKEY_H_
#include <cstdint>
using namespace std;
#include <vector>

namespace mindev::vmsconnection::security {
    class PublicKey{
        public:
            virtual std::vector<uint8_t> GetBytes()=0;
            virtual bool SetBytes(std::vector<uint8_t>& bytes)=0;
            virtual std::vector<uint8_t> Encrypt(std::vector<uint8_t>& content)=0;
            virtual bool Verify(std::vector<uint8_t>& content, std::vector<uint8_t>& digest)=0;
    };
}
#endif