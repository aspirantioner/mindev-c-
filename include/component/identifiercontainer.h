#ifndef IDENTIFIERCONTAINER_H_
#define IDENTIFIERCONTAINER_H_


#include "mindev/include/component/identifierwrapper.h"
#include <vector>

namespace mindev::component{
    class IdentifierContainer{
private:
    std::vector<IdentifierWrapper> identifierWrappers;
public:
    IdentifierContainer(){}
    inline int Length(){return this->identifierWrappers.size();}
    inline void Clear(){identifierWrappers.clear();}
    inline void AddElement(const IdentifierWrapper& elem){this->identifierWrappers.emplace_back(elem);}
    inline std::optional<std::reference_wrapper<IdentifierWrapper>> GetElement(int index){
        if(index>=this->Length()){
            return std::nullopt;
        }
        return this->identifierWrappers[index];
    }
    inline std::optional<std::reference_wrapper<IdentifierWrapper>> GetElementByType(const mindev::encoding::VlInt& vlnt){
        for(auto elem:this->identifierWrappers){
            if(elem.GetTlvType()==const_cast<mindev::encoding::VlInt&>(vlnt)){
                return elem;
            }
        }
        return std::nullopt;
    }
    inline void SetElement(int index,const IdentifierWrapper& wrapper){
        if(index>=this->Length()){
            return;
        }
        this->identifierWrappers[index] = wrapper;
    }
    inline std::vector<IdentifierWrapper>& GetIdentifierWrappers(){
        return this->identifierWrappers;
    }
    };
}

#endif
