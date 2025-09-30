#ifndef TIMEUTILS_H_
#define TIMEUTILS_H_

#include <chrono>

namespace timeutils {
    long long GetCurrentTime(){
        // 获取当前时间点
        auto now = std::chrono::system_clock::now();
    
        // 转为毫秒时间戳
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
                          now.time_since_epoch()
                      ).count();
        long long curTime = millis; // 与 Java long 对应
        return curTime;
    }
}


#endif