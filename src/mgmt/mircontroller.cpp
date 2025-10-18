#include "mindev/include/mgmt/mircontroller.h"

namespace mindev::mgmt{
MIRController MIRController::CreateMIRController(const LogicFaceBuilderInterface& logicFaceBuilderInterface,bool autoShutdown,const mindev::security::KeyChain& keyChain){
    MIRController mirController;
    // 记录 LogicFace 构造器，之后发起命令时，可以使用这个构造器构造一个逻辑接口发起命令请求
    mirController.logicFaceBuilderInterface=logicFaceBuilderInterface;
    mirController.autoShutdown=autoShutdown;
    mirController.keyChain=keyChain;
    return mirController;
}
std::optional<CommandExecutor> MIRController::PrepareCommandExecutor(const IControlCommand& command){
    auto logicFace=this->logicFaceBuilderInterface.LogicFaceBuilder();
    if(!logicFace.has_value()){ 
        return std::nullopt;
    }
    CommandExecutor commandExecutor;
    commandExecutor.Init(command,logicFace.value());
    commandExecutor.SetAutoShutdown(this->autoShutdown);
    commandExecutor.SetKeyChain(this->keyChain);
    return commandExecutor;
}

}