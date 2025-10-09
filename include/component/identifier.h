#ifndef IDENTIFIER_H_
#define IDENTIFIER_H_

#include "mindev/include/component/identifiercomponentcontainer.h"
#include "mindev/include/component/tlvcomponentbase.h"

namespace mindev::mgmt {
    class ControlParameters;
}

namespace mindev::component{
    
    class Identifier:public mindev::encoding::IEncodingAble,public TlvComponentBase{
public:
    typedef std::shared_ptr<Identifier> ptr;
    Identifier(){}
    static std::optional<Identifier> BuildIdentifierByBlock(mindev::encoding::Block& block);
    static std::optional<Identifier> BuildIdentifierByString(const std::string& identifierString);
    static std::optional<Identifier> BuildIdentifierByComponents(const IdentifierComponentContainer& container);
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    inline IdentifierComponentContainer GetComponents()const{return this->components;};
    inline std::optional<std::reference_wrapper<IdentifierComponent>> Get(int index){return this->GetComponents().GetElement(index);}
    std::string ToUri();
    std::string ToUriTemp();
    std::string ToString();
    inline bool Empty(){return this->components.Length()==0;}; 
    inline int Size(){return this->components.Length();};
    inline std::optional<Identifier> GetPrefix(int num){auto val = this->GetComponents().GetPrefix(num);
        if(!val.has_value()){
            return std::nullopt;
        }
        return Identifier::BuildIdentifierByComponents(val.value());
    };
    inline std::optional<Identifier> GetSubIdentifier(int startIndex,int num){
        auto val = this->components.GetSubIdentifierContainer(startIndex, num);
        if(!val.has_value()){
            return std::nullopt;
        }
        return Identifier::BuildIdentifierByComponents(val.value());
    }
    inline bool IsValid(){return this->components.Length()>0;}
    inline void Append(const IdentifierComponent& component){
        this->components.AddElement(component);
    }
    bool AppendCommandParameters(mindev::mgmt::ControlParameters& parameters);
    bool AppendVersionNumber(long versionNumber);
    bool AppendFragmentNumber(long fragmentNumber);
private:
    static const std::string identifier_split_str;
    IdentifierComponentContainer components;
    };
}

#endif
