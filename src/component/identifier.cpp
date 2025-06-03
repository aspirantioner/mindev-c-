#include "mindev/include/component/identifier.h"
#include "mindev/include/common/stringutils.h"
#include "mindev/include/component/identifiercomponent.h"
#include "mindev/include/encoding/block.h"
#include "mindev/include/encoding/elementcontainer.h"
#include "mindev/include/encoding/selfencodingbase.h":
#include <optional>

mindev::component::IdentifierComponent BuildIdentifierComponentByBlock(mindev::encoding::Block& block);
mindev::component::IdentifierComponent BuildIdentifierComponentByVersionNumber(long versionNumber);
mindev::component::IdentifierComponent BuildIdentifierComponentByFragmentNumber(long FragmentNumber);
using namespace mindev::encoding;
namespace mindev::component{
    const std::string mindev::component::Identifier::identifier_split_str = "/";
    std::optional<Identifier> Identifier::BuildIdentifierByBlock(mindev::encoding::Block& block){
        if(!block.ParseSubElements()){
            return std:: nullopt;
        }
        if(block.GetSubElements().Length()<1){
            return std::nullopt;
        }
        Identifier res;
        res.WireDecode(block);
        return res;
    }
    std::optional<Identifier> Identifier::BuildIdentifierByString(const std::string& identifierString){
        if(stringutils::StartWith(identifierString,identifier_split_str)){
            return  std::nullopt;
        }
        if(identifierString==identifier_split_str){
            IdentifierComponentContainer components;
            components.AddElement(IdentifierComponent(identifierString));
            return BuildIdentifierByComponents(components);
        }
        auto componentStrings = stringutils::SplitBySubstr(identifierString, identifier_split_str);
        IdentifierComponentContainer components;
        components.AddElement(IdentifierComponent(identifierString));
        for(int i = 1;i<componentStrings.size();i++){
            components.AddElement(IdentifierComponent(componentStrings[i]));
        }
        return BuildIdentifierByComponents(components);
    }
    std::optional<Identifier> Identifier::BuildIdentifierByComponents(const IdentifierComponentContainer& container){
        if(container.Length()<=0){
            return std::nullopt;
        }
        Identifier res;
        for(const auto elem:static_cast<IdentifierComponentContainer>(container).GetIdentifierComponents()){
            res.GetComponents().AddElement(elem);
        }
    }
    int Identifier::WireEncode(mindev::encoding::Encoder& encoder){
        
        int totalLength = 0;
        // 编码 TLV-VALUE
        for (auto iter = this->components.GetIdentifierComponents().rbegin();iter!=this->components.GetIdentifierComponents().rend();iter++) {
            int tmpLen = iter->WireEncode(encoder);
            if (tmpLen < 0) {
                return -1;
            }
            totalLength += tmpLen;
        }

        // 编码 TLV-LENGTH
        int tmpLen = encoder.PrependVarNumber(new mindev::encoding::VlInt(totalLength));
        if (tmpLen < 0) {
            return -1;
        }
        totalLength += tmpLen;

        // 编码 TLV-TYPE

        tmpLen = encoder.PrependVarNumber(new mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifier));

        if (tmpLen < 0) {
            return -1;
        }
        totalLength += tmpLen;

        return totalLength;
    }
    bool Identifier::WireDecode(mindev::encoding::Block& block){
       if (!mindev::encoding::TLV::ExpectType(block.GetType(), new mindev::encoding::VlInt(mindev::encoding::TLV::TlvIdentifier))) {
            return false;
        }

        // 解析子 TLV
        if (!block.ParseSubElements()) {
            return false;
        }

        this->components.Clear();
        mindev::encoding::ElementContainer elementContainer = block.GetSubElements();
        for (auto elem:elementContainer.GetElements()) {
            auto tmp = BuildIdentifierComponentByBlock(elem);
            if(tmp.IsValid()){
                this->components.AddElement(tmp);
            }else{
                return false;
            }
        }
        return true;
    }
    std::string Identifier::ToUri(){
        std::string res = "";
        for(auto elem:this->components.GetIdentifierComponents()){
            res+=Identifier::identifier_split_str+elem.ToUri();
        }
        return res;
    }
    std::string Identifier::ToUriTemp(){
        std::string res = "";
        for(auto elem:this->components.GetIdentifierComponents()){
            res+=Identifier::identifier_split_str+elem.ToUriTemp();
        }
        return res;
    }
    std::string Identifier::ToString(){
        std::string res = "";
        for(auto elem:this->components.GetIdentifierComponents()){
            res+=Identifier::identifier_split_str+elem.ToString();
        }
        return res;
    }
    bool Identifier::AppendCommandParameters(ControlParameters& parameters){
        auto selfEncodingBase = mindev::encoding::SelfEncodingBase();
        auto block = selfEncodingBase.SelfWireEncode(parameters);
        if(!block.has_value()){
            return false;
        }
        auto buffer = block.value().GetRaw();
        this->Append(IdentifierComponent(buffer)); 
        return true;
    }
    bool Identifier::AppendVersionNumber(long versionNumber){
        auto res = BuildIdentifierComponentByVersionNumber(versionNumber);
        if(!res.IsValid()){
            return false;
        }
        this->Append(res);
        return true;
    }
    bool Identifier::AppendFragmentNumber(long fragmentNumber){
        auto res = BuildIdentifierComponentByFragmentNumber(fragmentNumber);
        if(!res.IsValid()){
            return false;
        }
        this->Append(res);
        return true;
    }
}
