#ifndef ONINTERESTINTERFACE_H_
#define ONINTERESTINTERFACE_H_
#include "mindev/include/packet/interest.h"
namespace mindev::logicface::callbackinterface{
class OnInterestInterface{
public:
    virtual void OnInterest(const mindev::packet::Interest& interest)=0;
};
}
#endif