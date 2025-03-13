#ifndef BC_CODER_H_
#define BC_CODER_H_
#include <vector>
using namespace std;
#include "mindev/include/vmsconnection/tcpnet/socket_channel.h"
namespace mindev::vmsconnection::code{
    
    class BCCoder {
        public:
            static inline void WriteUInt32ToVector(std::vector<uint8_t>& vec, uint32_t value) {
                // 将 uint32_t 拆分为 4 个字节，按小端序（低位字节先）写入
                vec.push_back(static_cast<uint8_t>(value & 0xFF));        // 低位字节
                vec.push_back(static_cast<uint8_t>((value >> 8) & 0xFF)); // 第二个字节
                vec.push_back(static_cast<uint8_t>((value >> 16) & 0xFF)); // 第三个字节
                vec.push_back(static_cast<uint8_t>((value >> 24) & 0xFF)); // 高位字节
            }
            static inline uint32_t ToLittleEndian(const std::vector<uint8_t>& buf) {
                if (buf.size() != 4) {
                    throw std::invalid_argument("Buffer must have exactly 4 bytes.");
                }
                
                // 结合4个字节（按小端顺序）
                uint32_t result = 0;
                result |= static_cast<uint32_t>(buf[0]) << 0;  // 最低字节
                result |= static_cast<uint32_t>(buf[1]) << 8;  // 次低字节
                result |= static_cast<uint32_t>(buf[2]) << 16; // 次高字节
                result |= static_cast<uint32_t>(buf[3]) << 24; // 最高字节
            
                return result;
            }
//             static  std::vector<uint8_t>   Encode(std::vector<uint8_t>& raw_msg); static func define and extern can't split
//             static  std::vector<uint8_t>   Decode(std::shared_ptr<mindev::vmsconnection::tcpnet::SocketChannel> channel);
            static  std::vector<uint8_t>   Encode(std::vector<uint8_t>& raw_msg){
                std::vector<uint8_t> code_msg;
                uint32_t msg_length = raw_msg.size();
                BCCoder::WriteUInt32ToVector(code_msg, BCCoder::magic_number);
                BCCoder::WriteUInt32ToVector(code_msg, msg_length);
                code_msg.insert(code_msg.end(), raw_msg.begin(), raw_msg.end());
                return code_msg;
            }
            static std::vector<uint8_t>   Decode(std::shared_ptr<mindev::vmsconnection::tcpnet::SocketChannel> channel){
                std::vector<uint8_t> decode_msg(sizeof(BCCoder::magic_number),'\0');
                uint32_t raw_msg_length = 0;
        #define ERROR_DO(condition)\
            if(condition){\
                decode_msg.clear();\
                goto end;\
            }
                ERROR_DO(channel->Read(decode_msg)!=decode_msg.size());
                OH_LOG_INFO(LOG_APP,"read magic number ok!");
                ERROR_DO(BCCoder::ToLittleEndian(decode_msg)!=BCCoder::magic_number);
                OH_LOG_INFO(LOG_APP,"verify magic number %{public}d ok!",magic_number);
                ERROR_DO(channel->Read(decode_msg)!=decode_msg.size());
                raw_msg_length = BCCoder::ToLittleEndian(decode_msg);
                decode_msg.resize(raw_msg_length);
                ERROR_DO(channel->Read(decode_msg)!=raw_msg_length);
                OH_LOG_INFO(LOG_APP,"read msg len %{public}d is ok!",raw_msg_length);
            end:
                return decode_msg;
            }
            const static uint32_t magic_number = 0x6b796868;
    };
}

#endif