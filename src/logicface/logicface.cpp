#include "mindev/include/logicface/logicface.h"
#include "mindev/include/logicface/tcptransport.h"
#include "mindev/include/logicface/udptransport.h"
#include "mindev/include/vmsconnection/tcpnet/socket_channel.h"
#include "mindev/include/mgmt/registerprefixhelper.h"
namespace mindev::logicface{
    bool LogicFace::InitWithTcp(const std::string& ip,u_short port){
        auto channel = std::make_shared<mindev::vmsconnection::tcpnet::SocketChannel>(std::make_shared<mindev::vmsconnection::tcpnet::IPAddress>(ip,port));
        if(!channel->Connect()){
            return false;
        }
        
        this->linkService = std::make_shared<LinkService>();
        this->linkService->logicFace =  shared_from_this();
        if(!this->linkService->Init(DefaultMtuSize)){
            return false;
        };

        this->transport = std::make_shared<TcpTransport>(channel,this->linkService);
        this->linkService->transport = this->transport;
        this->type = LogicFaceType::TCP;
        this->state = true;
        return true;
    }
    bool LogicFace::InitWithUdp(const std::string& ip,u_short port){
        auto channel = std::make_shared<mindev::vmsconnection::tcpnet::SocketChannel>(std::make_shared<mindev::vmsconnection::tcpnet::IPAddress>(ip,port));
        auto ptr = new UdpTransport();
        if(!ptr->Init(channel)){
            delete ptr;
            return false;
        };

//         this->linkService = std::make_shared<LinkService>(std::ref(*this));
        this->linkService = std::make_shared<LinkService>();
        this->linkService->logicFace =  shared_from_this();
        if(!this->linkService->Init(DefaultMtuSize)){
            return false;
        };
        ptr->linkService = this->linkService;
        this->transport = std::shared_ptr<UdpTransport>(ptr);
        this->linkService->transport = this->transport;
        this->type = LogicFaceType::UDP;
        this->state = true;
        return true;
    }
    std::optional<LogicFace::ptr> LogicFace::InitTcpLogicFace(const std::string& ip,u_short port,bool use_prefix,const mindev::security::KeyChain& keyChain){
        LogicFace::ptr face = std::make_shared<mindev::logicface::LogicFace>();
        if(!face->InitWithTcp(ip, port)){
            return std::nullopt;
        }
        if(use_prefix){
            std::string local_face_prefix = "/min/mir1/default/"+timeutils::GetCurrentTimeStr();
            face->SetKeyChain(keyChain);
            mindev::mgmt::RegisterPrefixHelper registerhelper;
            auto res = component::Identifier::BuildIdentifierByString(local_face_prefix);
            if(!res.has_value()){
                return std::nullopt;
            }
            if(!registerhelper.RegisterPrefix(res.value(), face, keyChain)){
                return std::nullopt;
            }
            
        }
        return face;
    }
};