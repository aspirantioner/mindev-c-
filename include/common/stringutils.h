#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace stringutils {
    static std::vector<std::string> SplitBySubstr(const std::string& input, const std::string& delimiter) {
        std::vector<std::string> result;
        size_t pos = 0, prev = 0;
    
        while ((pos = input.find(delimiter, prev)) != std::string::npos) {
            result.push_back(input.substr(prev, pos - prev));
            prev = pos + delimiter.length();
        }
    
        // Add remaining part
        result.push_back(input.substr(prev));
    
        return result;
    }
    static bool StartWith(const std::string& str, const std::string& prefix) {
        return str.size() >= prefix.size() &&
               std::equal(prefix.begin(), prefix.end(), str.begin());
    }
    static inline char ToHexChar(unsigned char n) {
        return "0123456789ABCDEF"[n & 0xF];
    }
    static inline unsigned char FromHexToChar(char c) {
        if (c >= '0' && c <= '9') {
            return static_cast<unsigned char>(c - '0');
        } else if (c >= 'a' && c <= 'f') {
            return static_cast<unsigned char>(c - 'a' + 10);
        } else if (c >= 'A' && c <= 'F') {
            return static_cast<unsigned char>(c - 'A' + 10);
        } else {
            return 100; // 标记非法
        }
    }
    static std::string Escape(const std::string& str) {
        std::ostringstream oss;
        for (unsigned char ch : str) {
            if ((ch >= 'a' && ch <= 'z') ||
                (ch >= 'A' && ch <= 'Z') ||
                (ch >= '0' && ch <= '9') ||
                ch == '-' || ch == '.' || ch == '_' || ch == '~') {
                oss << ch;
            } else {
                oss << '%'
                    << ToHexChar((ch & 0xF0) >> 4)
                    << ToHexChar(ch & 0x0F);
            }
        }
        return oss.str();
    }
    static std::string Unescape(const std::string& str) {
        std::ostringstream oss;
        size_t len = str.length();
    
        for (size_t i = 0; i < len; ++i) {
            char ch = str[i];
            if (ch == '%' && i + 2 < len) {
                unsigned char high = FromHexToChar(str[i + 1]);
                unsigned char low = FromHexToChar(str[i + 2]);
                if (high == 100 || low == 100) {
                    oss << ch; // 无效百分号，原样保留
                } else {
                    oss << static_cast<char>((high << 4) | low);
                    i += 2;
                }
            } else {
                oss << ch;
            }
        }
        return oss.str();
    }
}

#endif