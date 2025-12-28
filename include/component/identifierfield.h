#ifndef IDENTIFIERFIELD_H_
#define IDENTIFIERFIELD_H_

#include "mindev/include/component/identifiercontainer.h"
#include "mindev/include/component/tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

namespace mindev::component{
    class IdentifierField:public TlvComponentBase,public mindev::encoding::IEncodingAble{
private:
    IdentifierContainer identifiers;
public:
    IdentifierField(){}
    inline void AddIdentifier(const IdentifierWrapper& wrapper){
        this->identifiers.AddElement(wrapper);
    }
    inline std::optional<IdentifierWrapper> GetIdentifierByType(const mindev::encoding::VlInt& tlvType){
        return this->identifiers.GetElementByType(tlvType);
    }
    inline std::optional<IdentifierWrapper> GetIdentifier(int index){
        return this->identifiers.GetElement(index);
    }
    inline void SetIdentifier(int index,const IdentifierWrapper& wrapper){
        this->identifiers.SetElement(index, wrapper);
    }
    inline void ClearIdentifiers(){
        this->identifiers.Clear();
    }
    inline IdentifierContainer& GetIdentifiers(){
        return this->identifiers;
    }
    int WireEncode(mindev::encoding::Encoder& encoder) override ;
    bool WireDecode(mindev::encoding::Block& block) override ;
    };
}

#endif
