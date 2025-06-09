#include "mindev/include/encoding/selfencodingbase.h"

namespace mindev::encoding {
    std::optional<Block> SelfEncodingBase::SelfWireEncode(IEncodingAble& iEncodingAble){
        if(this->rawBlock.IsValid()){
            return this->rawBlock;
        }
        auto block = EasyEncoder(iEncodingAble);
        if(!block.has_value()){
            return std::nullopt;
        }
        this->rawBlock = block.value();
        return block;
    }
    std::optional<Block> SelfEncodingBase::EasyEncoder(IEncodingAble& iEncodingAble){
        Encoder encoder;
        encoder.EstimatorReset();
        auto targetLen = iEncodingAble.WireEncode(encoder);
        if(targetLen<0){
            return std::nullopt;
        }
        auto size1 = SizeT(targetLen);
        auto size2 = SizeT(0);
        if(!encoder.EncoderReset(size1,size2)){
            return std::nullopt;
        }
        auto buffer = encoder.GetBuffer();
        if(buffer.size()==0){
            return std::nullopt;
        }
        return Block::CreateBlockByBuffer(buffer, true);
    } 
}