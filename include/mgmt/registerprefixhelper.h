#ifndef REGISTERPREFIXHELPER_H_
#define REGISTERPREFIXHELPER_H_
#include "mindev/include/logicface/iregisterprefixhelper.h"
#include "mindev/include/component/identifier.h"
namespace mindev::mgmt{
class RegisterPrefixHelper:public mindev::logicface::IRegisterPrefixHelper{
public:
    RegisterPrefixHelper(){}
    /**
    * 注册前缀
    * @param identifier
    * @param face
    * @param keyChain
    * @return
    */
    bool RegisterPrefix(const mindev::component::Identifier& identifier,const mindev::logicface::LogicFace& face,const mindev::security::KeyChain& keyChain);
};
}
#endif