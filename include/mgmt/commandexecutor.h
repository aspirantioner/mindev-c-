#ifndef COMMANDEXECTUOR_H_
#define COMMANDEXECTUOR_H_

#include "mindev/include/logicface/logicface.h"
#include "mindev/include/mgmt/icontrolcommand.h"
#include "mindev/include/security/keychain.h"
#include "mindev/include/packet/interest.h"
#include "mindev/include/mgmt/controlresponse.h"
#include "mindev/include/packet/data.h"
#include <optional>

namespace mindev::mgmt{

class CommandExecutor{
private:
    /**
     * onReceiveFirstMetaData 收到命令请求的第一个回复包
     * @param data
     * @return
     */
    std::optional<ControlResponse> OnReceiveFirstMetaData(const mindev::packet::Data& data);
public:
    //默认兴趣包生存期
    static const int defaultInterestLifetime=4000;
    //默认TTL
    // @Description:
    //	1. 默认TTL为1，表示当前管理命令只能传递给一跳路由器，即只能做本地管理用
    //	2. 如果想通过控制管理命令做远程管理，需要显示设置这个值，将其设置为一个较大值，这样才能将命令兴趣包转发到多跳路由器上
    static const int defaultTTL=64;
    // 要执行的命令
    IControlCommand command;
    //命令兴趣包的生存周期
    long interestLifeTime;
    long ttl;
    mindev::logicface::LogicFace logicFace;
    mindev::security::KeyChain keyChain;
    bool autoShutdown;
    /**
     * Init 初始化命令执行器
     * @param command
     * @param logicFace
     */
    inline void Init(const IControlCommand& command,const mindev::logicface::LogicFace& logicFace){this->command=command;this->interestLifeTime=CommandExecutor::defaultInterestLifetime;this->ttl=CommandExecutor::defaultTTL;this->logicFace= logicFace;this->autoShutdown=false;};
    /**
     * GetKeyChain 获取用于签名的秘钥链
     * @return
     */
    inline mindev::security::KeyChain GetKeyChain()const{return this->keyChain;}
    /**
     * SetKeyChain 设置用于签名的秘钥链
     * @param keyChain
     */
    inline void SetKeyChain(const mindev::security::KeyChain& keyChain){this->keyChain=keyChain;}
    /**
     * GetInterestLifeTime 获取命令兴趣包的生存期
     * @return
     */
    inline long GetInterestLifeTime()const{return this->interestLifeTime;}
    /**
     * SetInterestLifeTime 设置命令兴趣包的生存期
     * @param interestLifeTime
     */
    inline void SetInterestLifeTime(long interestLifeTime){this->interestLifeTime=interestLifeTime;}
    /**
     * GetTtl 获取命令兴趣包的 TTL
     * @return
     */
    inline long GetTtl()const{return this->ttl;}
    /**
     * SetTtl 设置命令兴趣包的 TTL
     * @param ttl
     */
    inline void SetTtl(long ttl){this->ttl=ttl;}
    /**
     * GetAutoShutdown 获取当前命令执行器是否在命令执行完成后自动关闭
     * @return
     */
    inline bool IsAutoShutdown()const{return this->autoShutdown;}
    /**
     * SetAutoShutdown 设置当前命令执行器是否在命令执行完成后自动关闭
     * @param autoShutdown
     */
    inline void SetAutoShutdown(bool autoShutdown){this->autoShutdown=autoShutdown;}
    /**
     * Shutdown 命令请求结束之后，如果想要关闭使用的 LogicFace，需要调用本函数关闭LogicFace
     * @return
     */
    inline bool Shutdown(){return this->logicFace.ShutDown();}
    /**
     * newCommandInterest 根据请求命令构造对应的命令兴趣包
     * @return
     * @throws MgmtException
     */
    mindev::packet::Interest NewCommandInterest();
    /**
     * Start 开始执行命令
     * // @Description:
     * //	这是一个阻塞调用，会在命令请求结束之后返回一个结果
     * @return
     */
    std::optional<ControlResponse> Start();
    /**
     * buildPrefix 构造命令兴趣包请求前缀
     * @param command
     * @return
     */
    inline std::string BuildPrefix(IControlCommand& command){return command.GetTopPrefix()+"/"+command.GetModuleName()+"/"+command.GetAction();}
    
    
    
};

}


#endif