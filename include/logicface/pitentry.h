#ifndef PITENTRY_H_
#define PITENTRY_H_
#include "mindev/include/packet/interest.h"
#include "mindev/include/logicface/callbackinterface/ondatainterface.h"
#include "mindev/include/logicface/callbackinterface/onnackinterface.h"
#include "mindev/include/logicface/callbackinterface/ontimeoutinterface.h"
#include <memory>
namespace mindev::logicface{
class PendingPacket{
public:
    mindev::packet::Interest interest;
    long expireTime;
    std::shared_ptr<mindev::logicface::callbackinterface::OnDataInterface> onDataInterface;// 收到对应的数据包的处理函数
    std::shared_ptr<mindev::logicface::callbackinterface::OnTimeoutInterface> onTimeoutInterface;// 兴趣包超时的处理函数
    std::shared_ptr<mindev::logicface::callbackinterface::OnNackInterface> onNackInterface;// 兴趣包无路由的处理函数
    PitEntry(){};
};
}

#endif