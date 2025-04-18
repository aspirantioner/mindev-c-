#include "mindev/include/logicface/logicface.h"
#include "mindev/include/logicface/tcptransport.h"
#include "mindev/include/logicface/udptransport.h"
#include "mindev/include/vmsconnection/tcpnet/socket_channel.h"
#include "mindev/include/logicface/tcptransport.h"

namespace mindev::logicface{
    bool LogicFace::initWithTcp(std::string ip,u_short port){
        auto channel = std::make_shared<mindev::vmsconnection::tcpnet::SocketChannel>(std::make_shared<mindev::vmsconnection::tcpnet::IPAddress>(ip,port));
        if(!channel->Connect()){
            return false;
        }
        auto ptr = new TcpTransport();
        if(!ptr->init(channel)){
            delete ptr;
            return false;
        };
        this->Transport = std::shared_ptr<TcpTransport>(ptr);
        this->linkService = std::make_shared<LinkService>();
        this->linkService->init(DefaultMtuSize);
        this->type = LogicFaceType::TCP;
        return true;
    }
    bool LogicFace::initWithUdp(std::string ip,u_short port){
        auto channel = std::make_shared<mindev::vmsconnection::tcpnet::SocketChannel>(std::make_shared<mindev::vmsconnection::tcpnet::IPAddress>(ip,port));
//         if(!channel->Connect()){
//             return false;
//         }
        auto ptr = new UdpTransport();
        if(!ptr->init(channel)){
            delete ptr;
            return false;
        };
        this->Transport = std::shared_ptr<UdpTransport>(ptr);
        this->linkService = std::make_shared<LinkService>();
        this->linkService->init(DefaultMtuSize);
        this->type = LogicFaceType::UDP;
        return true;
    }
};