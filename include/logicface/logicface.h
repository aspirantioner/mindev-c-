#ifndef LOGICFACE_H_
#define LOGICFACE_H_

#include "./logicface_counters.h"
#include "./itransport.h"
#include "./linkservice.h"
#include <memory>
#include <sys/types.h>


namespace mindev::logicface{
    class LinkService;
    enum LogicFaceType{
        TCP = 0,
        UDP = 1,
        Ether = 2,
        Unix = 3,
        Inner = 4,
    };
    const int DefaultMtuSize = 9000;
    // 分片兴趣包发送情况
    static const int PENDING = -3;
    static const int FAIL = -2;
    static const int FINISHED = -1;
    class LogicFace{
public:
    typedef std::shared_ptr<LogicFace> ptr; 
    LogicFaceType type;
    long expire_time;
    bool state;
    LogicFaceCounters logicFaceCounters;
    ITransport::ptr Transport;
    LinkService::ptr linkService;
    bool InitWithTcp(const std::string& ip,u_short port);
    bool InitWithUdp(const std::string& ip,u_short port);
    inline bool ShutDown(){
        if(this->state){
           this->Transport->Close();
           this->state=false;
//            this.executorService.shutdown();
//            this.ITransport.close();
        }
        return true;
    }

    };
}

#endif