//LogicFaceBuilder ICN逻辑接口构造器
#ifndef LOGICFACEBUILDERINTERFACE_H_
#define LOGICFACEBUILDERINTERFACE_H_
#include <optional>
#include "mindev/include/logicface/logicface.h"

namespace mindev::mgmt{
class LogicFaceBuilderInterface{
public:
    virtual std::optional<mindev::logicface::LogicFace> LogicFaceBuilder(){return std::nullopt;};
};
}



#endif