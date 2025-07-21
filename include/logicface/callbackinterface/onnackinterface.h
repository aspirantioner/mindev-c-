#ifndef ONNACKINTERFACE_H_
#define ONNACKINTERFACE_H_
#include "mindev/include/packet/interest.h"
#include "mindev/include/packet/nack.h"
namespace mindev::logicface::callbackinterface{
class OnNackInterface{
public:
    virtual void OnNack(const mindev::packet::Interest& interest,const mindev::packet::Nack& nack)=0;
};
}
#endif