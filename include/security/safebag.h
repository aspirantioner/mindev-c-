#ifndef SAFEBAG_H_
#define SAFEBAG_H_

#include <cstdint>
#include <vector>
namespace mindev::security {
class SafeBag {
public:
    std::vector<uint8_t> GetValue() const{
        return value;
    }
    void SetValue(const std::vector<uint8_t> &value) {
        this->value = value;
    }
    SafeBag(){}
    SafeBag(const std::vector<uint8_t>& value){
        this->value = value;
    }
    private:
        std::vector<uint8_t> value;
};
}
#endif