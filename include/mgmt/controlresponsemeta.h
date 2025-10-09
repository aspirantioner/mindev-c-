#ifndef CONTROLRESPONSEMETA_H_
#define CONTROLRESPONSEMETA_H_

#include <optional>
#include "mindev/include/common/json.hpp"
//一个表示管理控制命令的元数据结构
namespace mindev::mgmt {
    class ControlResponse;
    class ControlResponseMeta{
public:
    //版本号
    long Version;
    //总的分片数
    long SliceNum;
    /**
     * CreateMetaDataControlResponse 创建一个表示元数据的返回响应
     * @param version
     * @param sliceNum
     * @return
     */
    static std::optional<ControlResponse> CreateMetaDataControlResponse(long version,long sliceNum);
    
    
    };
    // json 序列化支持
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ControlResponseMeta,Version,SliceNum);
}


#endif