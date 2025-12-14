//一个实现了LogicFaceBuildInterface接口的具体类
#ifndef CONCRETELOGICFACEBUILDER_H_
#define CONCRETELOGICFACEBUILDER_H_
#include "logicfacebuilderinterface.h"
#include "mindev/include/logicface/logicface.h"
namespace mindev::mgmt{
class ConcreteLogicFaceBuilder:public LogicFaceBuilderInterface{
private:
    mindev::logicface::LogicFace face;
public:
    typedef std::shared_ptr<ConcreteLogicFaceBuilder> ptr;
    ConcreteLogicFaceBuilder(){}
    ConcreteLogicFaceBuilder(const mindev::logicface::LogicFace& logicFace){this->face=logicFace;}
    inline std::optional<mindev::logicface::LogicFace> LogicFaceBuilder(){return face;}
    
    
};




}


#endif