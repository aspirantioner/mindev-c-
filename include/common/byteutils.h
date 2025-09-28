#ifndef BYTEUTILS_H_
#define BYTEUTILS_H_

#include <sys/types.h>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <type_traits>
#include <string>
#include <iomanip>
#include <sstream>
#include <random>
#include <limits>

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

template<typename T, typename = std::enable_if_t<std::is_same_v<T, uint8_t> || std::is_same_v<T, char>>>
std::string VectorToHex(const std::vector<T>& data,bool need_space = false) {
    std::ostringstream oss;
    oss << std::uppercase << std::hex << std::setfill('0');
    for (size_t i = 0; i < data.size(); ++i) {
        oss << std::setw(2) << (static_cast<unsigned int>(static_cast<unsigned char>(data[i])));
        if(need_space){
            if (i != data.size() - 1)
                oss << " "; // 每个字节之间加空格
        }
    }
    return oss.str();
}

template <typename T>
std::vector<T> GenerateRandomVector(size_t length) {
    static_assert(std::is_integral<T>::value, "T must be an integral type.");

    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dist(
        std::numeric_limits<T>::min(),
        std::numeric_limits<T>::max()
    );

    std::vector<T> result;
    result.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        result.push_back(static_cast<T>(dist(gen)));
    }

    return result;
}

// vector -> string
template<typename T>
std::string VectorToString(const std::vector<T>& vec) {
    static_assert(std::is_same<T, uint8_t>::value || std::is_same<T, char>::value,
                  "T must be uint8_t or char");
    return std::string(reinterpret_cast<const char*>(vec.data()), vec.size());
}

// string -> vector
template<typename T>
std::vector<T> StringToVector(const std::string& str) {
    static_assert(std::is_same<T, uint8_t>::value || std::is_same<T, char>::value,
                  "T must be uint8_t or char");
    const T* dataPtr = reinterpret_cast<const T*>(str.data());
    return std::vector<T>(dataPtr, dataPtr + str.size());
}

// uint8_t -> char
inline std::vector<char> Uint8ToChar(const std::vector<uint8_t>& src) {
    std::vector<char> dst(src.size());
    std::copy(src.begin(), src.end(), dst.begin());
    return dst;
}

// char -> uint8_t
inline std::vector<uint8_t> CharToUint8(const std::vector<char>& src) {
    std::vector<uint8_t> dst(src.size());
    std::copy(src.begin(), src.end(), dst.begin());
    return dst;
}
}


#endif