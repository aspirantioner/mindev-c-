#ifndef ONDATAINTERFACE_H_
#define ONDATAINTERFACE_H_
#include "mindev/include/packet/interest.h"
#include "mindev/include/packet/data.h"
namespace mindev::logicface::callbackinterface{
class OnDataInterface{
public:
    virtual void OnData(const mindev::packet::Interest& interest,const mindev::packet::Data& data)=0;
};
}


#endif