#ifndef SELFENCODINGBASE_H_
#define SELFENCODINGBASE_H_

/*
 * @Author: Hansen
 * @Description: 利用对接口的函数回调，实现对任意实现了 IEncodingAble 接口的对象进行自编码
 * @Date: 2025-04-11 15:55:12
 * @Copyright: MIN-Group；国家重大科技基础设施——未来网络北大实验室；深圳市信息论与未来网络重点实验室
 */

#include "mindev/include/encoding/block.h"
#include "/mindev/include/encoding/iencodingable.h"

namespace mindev::encoding {
    class SelfEncodingBase{
        private:
            //用来实现自编码的辅助结构
            Block rawBlock;
        public:
            inline Block GetRawBlock(){return this->rawBlock;};
            SelfEncodingBase(){};
            std::optional<Block> SelfWireEncode(mindev::encoding::IEncodingAble& iEncodingAble);
            std::optional<Block> EasyEncoder(mindev::encoding::IEncodingAble& iEncodingAble);
    };
}
#endif