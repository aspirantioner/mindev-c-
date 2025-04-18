#ifndef TEMPLATEINIT_H_
#define TEMPLATEINIT_H_

#include <type_traits>
#include <stdexcept>

class TemplateInit{
protected:
    // 小技巧，用于static_assert
    template<typename>
    static constexpr bool always_false = false;
};

#endif