#ifndef MGMTCOMMAND_H_
#define MGMTCOMMAND_H_
#include "mindev/include/packet/interest.h"
#include "mindev/include/component/identifier.h"

namespace mindev::logicface{
class MgmtCommand{
public:
    /**
     *
     * @param identifier
     * @return
     */
    static std::optional<mindev::packet::Interest> CreateRegisterIdentifierInterest(const mindev::component::Identifier& identifier);
};
}
#endif