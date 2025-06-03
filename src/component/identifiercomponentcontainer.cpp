#include "mindev/include/component/identifiercomponentcontainer.h"

namespace mindev::component{
    std::optional<IdentifierComponentContainer> IdentifierComponentContainer::GetPrefix(int num){
        if(num>this->Length()){
            return std::nullopt;
        }
        IdentifierComponentContainer res;
        for(int i = 0;i<num;i++){
            res.AddElement(this->GetIdentifierComponents()[i]);
        }
        return res;
    }
    std::optional<IdentifierComponentContainer> IdentifierComponentContainer::GetSubIdentifierContainer(int startIndex,int num){
        if(startIndex+num>this->Length()){
            return std::nullopt;
        }
        IdentifierComponentContainer res;
        for(int i = startIndex;i<startIndex+num;i++){
            res.AddElement(this->GetIdentifierComponents()[i]);
        }
        return res;
    }
}
