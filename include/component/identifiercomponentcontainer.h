#ifndef IDENTIFIERCOMPONENTCONTAINER_H_
#define IDENTIFIERCOMPONENTCONTAINER_H_

#include "identifiercomponent.h"

namespace mindev::component{
    class IdentifierComponentContainer{
public:
    typedef std::shared_ptr<IdentifierComponentContainer> ptr;
    inline size_t Length()const{return this->identifierComponents.size();};
    inline std::optional<std::reference_wrapper<IdentifierComponent>> GetElement(int index){if(index<0 || index>=this->Length()){return std::nullopt;}auto iter = this->identifierComponents.begin();
        std::advance(iter,index);auto res = *iter;return res;};
    inline std::vector<IdentifierComponent> GetIdentifierComponents() const {return this->identifierComponents;};
    
    inline void Clear(){identifierComponents.clear();};
    inline void AddElement(const IdentifierComponent& identifierComponent) {
        identifierComponents.emplace_back(identifierComponent);
    }
    std::optional<IdentifierComponentContainer> GetPrefix(int num);
    std::optional<IdentifierComponentContainer> GetSubIdentifierContainer(int startIndex,int num);
private:
    std::vector<IdentifierComponent> identifierComponents;
    };
}

#endif
