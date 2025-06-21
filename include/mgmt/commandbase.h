#ifndef COMMANDBASE_H_
#define COMMANDBASE_H_

#include "mindev/include/mgmt/icontrolcommand.h"
#include "mindev/include/packet/interest.h"

namespace mindev::mgmt {
    class CommandBase:public IControlCommand{
public:
    inline static const std::string ManagementModuleFaceMgmt = "face-mgmt";
    inline static const std::string ManagementModuleFibMgmt = "fib-mgmt";
    inline static const std::string ManagementModuleCsMgmt = "cs-mgmt";
    std::string topPrefix;
    std::string moduleName;
    std::string action;
    ControlParameters parameters;
    /**
     * GetTopPrefix 获取顶级前缀
     * @return
     */
    inline std::string& GetTopPrefix(){return this->topPrefix;}
    /**
     * SetTopPrefix 设置顶级前缀
     * @param topPrefix
     */
    inline void SetTopPrefix(const std::string& topPrefix){this->topPrefix = topPrefix;}
    /**
     * GetModuleName 获取模块名称
     * @return
     */
    inline std::string& GetModuleName(){return this->moduleName;}
    /**
     * SetModuleName 设置模块名称
     * @param moduleName
     */
    inline void SetModuleName(const std::string& moduleName){this->moduleName = moduleName;}
    /**
     * GetAction 获取命令动作
     * @return
     */
    inline std::string& GetAction(){return this->action;}
    /**
     * SetAction 设置命令动作
     * @param action
     */
    inline void SetAction(const std::string& action){this->action = action;}
    /**
     * GetParameters 获取管理命令前缀
     * @return
     */
    inline ControlParameters& GetParameters(){return this->parameters;}
    /**
     * SetParameters 设置管理命令前缀
     * @param parameters
     */
    inline void SetParameters(const ControlParameters& parameters){this->parameters = parameters;}
    /**
     * 根据传入的控制参数和前缀创建一个命令兴趣包
     * @param parameters 控制参数
     * @param prefix     前缀 /min-mir/mgmt/localhost
     * @return
     */
    static std::optional<mindev::packet::Interest> CreateCommandIdentifierInterest(const ControlParameters& parameters,const std::string& prefix);
    static std::optional<ControlParameters> ParseControlParameters(const mindev::packet::Interest&);
    
    
    };
}

#endif