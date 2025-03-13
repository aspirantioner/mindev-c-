#include "mindev/include/vmsconnection/code/bc_coder.h"
#include "mindev/include/vmsconnection/tcpnet/socket_channel.h"

namespace mindev::vmsconnection::code{
    
//      std::vector<uint8_t>   Encode(std::vector<uint8_t>& raw_msg){
//         std::vector<uint8_t> code_msg;
//         uint32_t msg_length = raw_msg.size();
//         BCCoder::WriteUInt32ToVector(code_msg, BCCoder::magic_number);
//         BCCoder::WriteUInt32ToVector(code_msg, msg_length);
//         code_msg.insert(code_msg.end(), raw_msg.begin(), raw_msg.end());
//         return code_msg;
//     }
//     std::vector<uint8_t>   Decode(std::shared_ptr<mindev::vmsconnection::tcpnet::SocketChannel> channel){
//         std::vector<uint8_t> decode_msg(sizeof(BCCoder::magic_number),0);
//         uint32_t raw_msg_length = 0;
// #define ERROR_DO(condition)\
//     if(condition){\
//         decode_msg.clear();\
//         goto end;\
//     }
//         ERROR_DO(channel->Read(decode_msg)!=decode_msg.size());
//         ERROR_DO(BCCoder::ToLittleEndian(decode_msg)!=BCCoder::magic_number);
//         ERROR_DO(channel->Read(decode_msg)!=decode_msg.size());
//         raw_msg_length = BCCoder::ToLittleEndian(decode_msg);
//         decode_msg.resize(raw_msg_length);
//         ERROR_DO(channel->Read(decode_msg)!=raw_msg_length);
//     end:
//         return decode_msg;
//     }

}