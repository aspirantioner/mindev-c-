#ifndef IREGISTERPREFIXHELPER_H_
#define IREGISTERPREFIXHELPER_H_
#include "mindev/include/component/identifier.h"
#include "mindev/include/logicface/logicface.h"
#include "mindev/include/security/keychain.h"
namespace mindev::logicface{
class IRegisterPrefixHelper{
public:
    virtual bool RegisterPrefix(const mindev::component::Identifier& identifier,std::shared_ptr<mindev::logicface::LogicFace> face,const mindev::security::KeyChain& keyChain)=0;
};
}
#endif