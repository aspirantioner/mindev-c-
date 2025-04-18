
#ifndef SIGNATUREVALUE_H_
#define SIGNATUREVALUE_H_

#include "tlvcomponentbase.h"
#include "mindev/include/encoding/iencodingable.h"

#include <vector>

namespace mindev::component{
    class SignatureValue{
public:
    typedef std::shared_ptr<SignatureValue> ptr;
private:
    std::vector<char> value;
    };
}

#endif
