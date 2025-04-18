#ifndef TLV_H_
#define TLV_H_

namespace mindev::encoding {
    class TLV{
public:
    ////// 一级：网络分组级别TLV号分配（0 ~ 49）
    static const int TlvInvalid    = 0; // 无效包
    static const int TlvPacketMINCommon     = 5; // 通用MIN包
    static const int TlvPacketMINManagement = 6; // MIN管理包
    static const int TlvPacketMINIP         = 7; // MIN支持IP包

    ////// 二级：网络包分区TLV号分配 （50 ~ 99）
    static const int TlvIdentifierField       = 50; // 目的标识区
    static const int TlvSignatureField        = 51; // 数字签名区
    static const int TlvReadOnlyField         = 52; // 只读数据区
    static const int TlvMutableField          = 53; // 可变数据区
    static const int TlvMutableProtectField   = 54; // 可变数据区中的保护区
    static const int TlvMutableDangerousField = 55; // 可变数据区中的非受保护区

    ////// 组件 （100 -> 500）
    // 标识分配
    static const int TlvIdentifierComponent       = 100; // 标识名称组件
    static const int TlvIdentifier                = 101; // 标识
    static const int TlvIdentifierCommon          = 102; // 身份标识
    static const int TlvIdentifierContentInterest = 103; // 内容兴趣标识
    static const int TlvIdentifierContentData     = 104; // 内容数据标识

    // 数字签名
    static const int TlvSignatureValue = 200; // 签名值
    static const int TlvSignatureInfo  = 201; // 签名参数
    static const int TlvSignatureType  = 202; // 签名类型
    static const int TlvKeyLocator     = 203; // 指示证书或公钥的位置

    static const int TlvPayload          = 204; // 网络包负载
    static const int TlvCanBePrefix      = 205; // 是否可以被较长的数据包前缀匹配
    static const int TlvMustBeRefresh    = 206; // 是否强制只拉取新鲜的数据
    static const int TlvInterestLifeTime = 207; // 兴趣包生存期
    static const int TlvNonce            = 208; // 随机数
    static const int TlvHopLimit         = 209; // 跳数限制
    static const int TlvFreshnessPeriod  = 210; // 数据包新鲜时间
    static const int TlvCongestionMark   = 211; // 拥塞标记
    static const int TlvTTL              = 212; // Time to live
    static const int TlvNackHeader       = 213; // Nack header
    static const int TlvNoCache             = 214; // No Cache
    static const int TlvIncomingLogicFaceId = 215; // 入口逻辑接口地址

    // 管理通信协议(old version)
//    static const int TlvSliceNumber    = 211; // 分片数量
//    static const int TlvSliceSize      = 212; // 分片大小
//    static const int TlvTlvLogicFaceId = 213; // 逻辑接口id
//    static const int TlvRemoteAddr     = 214; // 源端地址
//    static const int TlvLocalAddr      = 215; // 本地地址
//    static const int TlvMtu            = 216; // 最大传输单元
//    static const int TlvRet            = 217; // bool类型，成功或失败
//    static const int TlvOrigin         = 218; //
//    static const int TlvCost           = 219; // 链路开销
//    static const int TlvExpires        = 220; // LogicFace超时时间，-1为不超时（never）

    // 管理通信协议
    static const int TlvManagementControlParameters = 220; // 控制命令参数
    static const int TlvManagementLogicFaceId       = 221; // 逻辑接口Id
    static const int TlvManagementUri               = 222; // 逻辑接口地址，例如: tcp://192.168.1.1:13899，存在localUri时，也可表示remoteUri

    // 管理通信协议 -> LogicFaceManager
    static const int TlvManagementCost                 = 223; // 链路开销
    static const int TlvManagementLogicFacePersistency = 224; // 逻辑接口持久性
    static const int TlvManagementUriScheme            = 225; // 逻辑接口地址采用的模式，例如：tcp
    static const int TlvManagementMtu                  = 226; // 最大传输单元
    static const int TlvManagementCapacity             = 227; // CS容量
    static const int TlvManagementCount                = 228; // 删除的CS条目的数量
    static const int TlvManagementExpireTime           = 229; // 超时时间
    static const int TlvManagementLocalUri             = 230; // 逻辑接口地址，例如: tcp://192.168.1.1:13899，存在localUri时，也可表示remoteUri
    static const int TlvManagementPrefix               = 240; // 前缀
    static const int TlvManagementPasswd               = 241; // 密码
    static const int TlvManagementCommonString         = 242; // 通用字符串参数

    // LpPacket
    static const int TlvLpPacket            = 250; // LpPacket
    static const int TlvLpPacketHeader      = 251; // LpPacket Header
    static const int TlvLpPacketFragmentId  = 252; // LpPacket 分片id
    static const int TlvLpPacketFragmentNum = 253; // LpPacket 分片数
    static const int TlvLpPacketFragmentSeq = 254; // LpPacket 分片号

    // 目前已分配的最大的Tlv值，第一轮分配的最大值为500，超过该值则断定为不合法
    // TODO: 目前TLV值的分配，第一轮分配都在500以内，如果以后分配更高值时，需要修改此处的限制
    static const int MaxTlvNum = 500;
    };
}

#endif