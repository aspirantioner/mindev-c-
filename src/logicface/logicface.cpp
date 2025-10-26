#include "mindev/include/logicface/logicface.h"
#include "mindev/include/logicface/tcptransport.h"
#include "mindev/include/logicface/udptransport.h"
#include "mindev/include/vmsconnection/tcpnet/socket_channel.h"

namespace mindev::logicface{
    bool LogicFace::InitWithTcp(const std::string& ip,u_short port){
        auto channel = std::make_shared<mindev::vmsconnection::tcpnet::SocketChannel>(std::make_shared<mindev::vmsconnection::tcpnet::IPAddress>(ip,port));
        if(!channel->Connect()){
            return false;
        }
        auto ptr = new TcpTransport();
        if(!ptr->Init(channel)){
            delete ptr;
            return false;
        };

        this->linkService = std::make_shared<LinkService>(std::ref(*this));
        if(!this->linkService->Init(DefaultMtuSize)){
            return false;
        };
        ptr->linkService = this->linkService;
        this->transport = std::shared_ptr<TcpTransport>(ptr);
        this->linkService->transport = this->transport;
        this->type = LogicFaceType::TCP;
        this->state = true;
        return true;
    }
    bool LogicFace::InitWithUdp(const std::string& ip,u_short port){
        auto channel = std::make_shared<mindev::vmsconnection::tcpnet::SocketChannel>(std::make_shared<mindev::vmsconnection::tcpnet::IPAddress>(ip,port));
//         if(!channel->Connect()){
//             return false;
//         }
        auto ptr = new UdpTransport();
        if(!ptr->Init(channel)){
            delete ptr;
            return false;
        };

        this->linkService = std::make_shared<LinkService>(std::ref(*this));
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
    std::optional<LogicFace> LogicFace::InitTcpLogicFace(const std::string& ip,u_short port,bool use_prefix){
        LogicFace face;
        if(!face.InitWithTcp(ip, port)){
            return std::nullopt;
        }
        if(use_prefix){
            
        }
        return face;
    }
};