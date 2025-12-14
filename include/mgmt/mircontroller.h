//* @Description: MIRController 表示一个 MIR 控制器
//	主要用于和 MIR 进行管理命令通信
#ifndef MIRCONTROLLER_H_
#define MIRCONTROLLER_H_

#include "mindev/include/security/keychain.h"
#include "./logicfacebuilderinterface.h"
#include "./icontrolcommand.h"
#include "./commandexecutor.h"
#include <optional>
namespace mindev::mgmt{
class MIRController{
public:
    // LogicFace 构造工厂
    LogicFaceBuilderInterface::ptr logicFaceBuilderInterface;
    mindev::security::KeyChain keyChain;
    bool autoShutdown;
    /**
     * reateMIRController 创建一个 MIRController
     * @param logicFaceBuilderInterface LogicFaceICN 构造器，每次执行需要返回一个新构造的逻辑接口
     * @param autoShutdown
     * @param keyChain
     * @return
     */
    static MIRController CreateMIRController(std::shared_ptr<LogicFaceBuilderInterface> logicFaceBuilderInterface,bool autoShutdown,const mindev::security::KeyChain& keyChain);
    /**
     * PrepareCommandExecutor 构造一个命令执行器用来执行命令
     * @param command
     * @return
     */
    std::optional<CommandExecutor> PrepareCommandExecutor(IControlCommand::ptr command);
};

}






#endif