#ifndef INITIALABLE_H_
#define INITIALABLE_H_

namespace mindev::component{
    class InitialAble{
public:
    // 将组件标记为已初始化
    void doInitial(){this->initial= true;};

    // 判断当前组件是否已经初始化
    bool isInitial(){return this->initial;};
protected:
    bool initial = false;
    };
}

#endif
