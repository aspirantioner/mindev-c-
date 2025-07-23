#ifndef TIMEOUTEVENT_H_
#define TIMEOUTEVENT_H_
#include <string>
namespace mindev::logicface{
class TimeoutEvent{
public:
    std::string key;
    long timeoutTime;
    TimeoutEvent(){};
    TimeoutEvent(std::string key, long timeoutTime): key(key), timeoutTime(timeoutTime) {};
};
}

#endif