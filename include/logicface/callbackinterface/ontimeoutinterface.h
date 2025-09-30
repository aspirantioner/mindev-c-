#ifndef ONTIMEOUTINTERFACE_H_
#define ONTIMEOUTINTERFACE_H_
#include "mindev/include/packet/interest.h"
namespace mindev::logicface::callbackinterface{
class OnTimeoutInterface{
public:
    virtual void OnTimeout(const mindev::packet::Interest& interest)=0;
};
}
#endif