#include "mindev/include/mgmt/controlresponsemeta.h"
#include "mindev/include/mgmt/controlresponse.h"

namespace mindev::mgmt{
    std::optional<ControlResponse> ControlResponseMeta::CreateMetaDataControlResponse(long version,long sliceNum){
        ControlResponse response;
        response.code=ControlResponse::ControlResponseCodeContinue;
        ControlResponseMeta meta;
        meta.version=version;
        meta.sliceNum=sliceNum;
        response.SetMeta(meta);
        return response;
    }
}