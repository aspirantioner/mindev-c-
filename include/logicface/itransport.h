#ifndef ITRANSPORT_H_
#define ITRANSPORT_H_

#include <string>

namespace mindev::logicface{
    class ITransport{
public:
        typedef std::shared_ptr<ITransport> ptr;
        virtual void close(){};
        virtual bool send(){return true;};
        virtual void receive(){};
        virtual std::string getRemoteUri() {return "";};
        virtual std::string getLocalUri() {return "";};
        virtual std::string getRemoteAddr() {return "";};
        virtual std::string getLocalAddr() {return "";};
        virtual bool setReadTimeout(long duration) {return true;};
    };
}

#endif