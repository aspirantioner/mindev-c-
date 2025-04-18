#ifndef BYTEUTILS_H_
#define BYTEUTILS_H_

#include <sys/types.h>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <type_traits>

namespace byteutils {

template<typename T>
T ToValue(const std::vector<char>& bytes, uint offset=0,bool little_endian = true) {
    static_assert(std::is_integral_v<T>, "Only integral types are supported.");

    if (bytes.size()-offset < sizeof(T)) {
        throw std::runtime_error("Not enough bytes to convert to target type.");
    }

    T value = 0;

    if (little_endian) {
        std::memcpy(&value, bytes.data()+offset, sizeof(T));
    } else {
        for (size_t i = 0; i < sizeof(T); ++i) {
            reinterpret_cast<uint8_t*>(&value)[sizeof(T) - 1 - i] = static_cast<uint8_t>(bytes[i+offset]);
        }
    }

    return value;
}

// 任意整数类型 转 vector<char>
template<typename T>
std::vector<char> FromValue(T value, bool little_endian = true) {
    static_assert(std::is_integral_v<T>, "Only integral types are supported.");

    std::vector<char> bytes(sizeof(T));

    if (little_endian) {
        std::memcpy(bytes.data(), &value, sizeof(T));
    } else {
        for (size_t i = 0; i < sizeof(T); ++i) {
            bytes[i] = static_cast<char>(reinterpret_cast<uint8_t*>(&value)[sizeof(T) - 1 - i]);
        }
    }
    return bytes;
}
}


#endif