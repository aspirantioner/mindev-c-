#ifndef SSL_TYPE_H_
#define SSL_TYPE_H_

namespace mindev::vmsconnection::ssltype{
    
    typedef enum{
        Encrypted = 0,
        NotEncrypted
    } EncryptType; 
    
    typedef enum{
        Normal = 0,
        Setup,
        Resp
    }SSLMessageType;
    
    typedef  enum{
        Success=200,
        BadRequest=400,
        NotAuthorized=403,
        ServerError=500
    }SSLRespMessageType;
}

#endif