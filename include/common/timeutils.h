#ifndef TIMEUTILS_H_
#define TIMEUTILS_H_

#include <chrono>

namespace timeutils {
    static std::string GetCurrentTimeStr() {
        using namespace std::chrono;

        // 获取当前时间点
        auto now = system_clock::now();

        // 转为毫秒时间戳
        auto millis = duration_cast<milliseconds>(now.time_since_epoch()).count();

        // 转为秒
        auto sec = duration_cast<seconds>(now.time_since_epoch());
        std::time_t t = sec.count();

        // 获取毫秒部分
        long millisecond = millis % 1000;

        // 转为本地时间
        std::tm tm_time;
        localtime_r(&t, &tm_time); // 线程安全

        // 格式化输出 yyyyMMddHHmmssSSS
        std::ostringstream oss;
        oss << std::put_time(&tm_time, "%Y%m%d%H%M%S") 
            << std::setw(3) << std::setfill('0') << millisecond;

        return oss.str();
    }
    static long long GetCurrentTime(){
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