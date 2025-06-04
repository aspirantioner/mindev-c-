//定义了定义了一个网络包应该实现哪些和分区交互的方法
#ifndef INTERACTWITHFIELD_H_
#define INTERACTWITHFIELD_H_

namespace mindev::packet{
    class InteractWithField{
public:
    /**
     * 将包的属性填充到网络包的四个分区当中
     * @return
     */
    virtual bool FillDataToFields()=0;
    /**
     * 从网络包的四个分区当中提取出特定网络包的相关属性
     * @return
     */
    virtual bool ExtraDataFromFields()=0;
    };
}

#endif
