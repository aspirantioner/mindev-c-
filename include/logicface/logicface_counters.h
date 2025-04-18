#ifndef LOGICFACE_COUNTERS_H_
#define LOGICFACE_COUNTERS_H_

#include <memory>
namespace mindev::logicface{
    
    class LogicFaceCounters{
    
public:
    long InCPacketN;    // 从本接口流入的普通推式包的个数
    long OutCPacketN;   // 从本接口流出的普通推式包的个数
    long DropCPacketN;  // 从本接口流入后被丢弃的普通推式包的个数
    long InInterestN;   // 从本接口流入的兴趣包的个数
    long OutInterestN;  // 从本接口流出的兴趣包的个数
    long DropInterestN; // 从本接口流入后被丢弃的兴趣包的个数
    long InDataN;       // 从本接口流入的数据包的个数
    long OutDataN;      // 从本接口流出的数据包的个数
    long DropDataN;     // 从本接口流入后被丢弃的数据包的个数
    long InNackN;       // 从本接口流入的Nack包的个数
    long OutNackN;      // 从本接口流出的Nack包的个数
    long DropNackN;     // 从本接口流入后被丢弃的Nack包的个数
    long InBytesN;      // 从本接口流入的数据字节数
    long OutBytesN;     // 从本接口流出的数据字节数
    typedef std::shared_ptr<LogicFaceCounters> ptr;
    };
}

#endif