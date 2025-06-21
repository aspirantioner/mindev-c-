#ifndef CONTROLRESPONSEMETA_H_
#define CONTROLRESPONSEMETA_H_

#include <optional>

//一个表示管理控制命令的元数据结构
namespace mindev::mgmt {
    class ControlResponse;
    class ControlResponseMeta{
public:
    //版本号
    long version;
    //总的分片数
    long sliceNum;
    /**
     * CreateMetaDataControlResponse 创建一个表示元数据的返回响应
     * @param version
     * @param sliceNum
     * @return
     */
    static std::optional<ControlResponse> CreateMetaDataControlResponse(long version,long sliceNum);
    
    
    };
}


#endif