import os
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('--file', type=str)
parser.add_argument("--line",type=int)
if __name__ == "__main__":
    args = parser.parse_args()

    src_dir = "D:\OpenHarmony\MyApplication\entry\src\main\cpp\mindev\include\component"
    dst_dir = "D:\OpenHarmony\MyApplication\entry\src\main\cpp\mindev\src\component"
    cache = []
    class_name = args.file
    if args.file.find("ControlParameter")!=-1:
        var = args.file[len("ControlParameter"):]
    else:
        var = args.file
        
    args.file = args.file.lower()
    with open(os.path.join(src_dir,args.file+".h"),"r") as f:
        cache = f.readlines()
        if cache[0] == '\n':
            cache.pop(0)
        cache.insert(args.line,"    int WireEncode(mindev::encoding::Encoder& encoder) override ;\n")
        cache.insert(args.line+1,"    bool WireDecode(mindev::encoding::Block& block) override ;\n")
    
    with open(os.path.join(src_dir,args.file+".h"),"w") as f:
        f.writelines(cache)
        cache.clear()
    
    with open(os.path.join(dst_dir,args.file+".cpp"),"w") as f:
        cpp_template_txt = f"""#include "mindev/include/component/{args.file}.h"

namespace mindev::component{{
    int {class_name}::WireEncode(mindev::encoding::Encoder& encoder){{
        int totalLength = 0;
        int tmpLen = encoder.PrependNonNegativeInteger(this->{var.lower()});
        if(tmpLen<0){{
            return -1;
        }}
        totalLength += tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){{
            return -1;
        }}
        totalLength+=tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::TLV::TlvManagement{var});
        if(tmpLen<0){{
            return -1;
        }}
        totalLength+=tmpLen;
        return totalLength;
    }}
    bool {class_name}::WireDecode(mindev::encoding::Block& block){{
        if(!mindev::encoding::TLV::ExpectType(block.GetType(), mindev::encoding::VlInt(mindev::encoding::TLV::TlvManagement{var}))){{
            return false;
        }}
        auto value = mindev::encoding::TLV::ReadNonNegativeInteger(block.GetValue(), 0, bigint::_bigint_to<int>(block.GetLength().GetVlIntValue()));
        if(value<0){{
            return false;
        }}
        this->Set{var}(value);
        return true;
    }}
}}
"""
        f.write(cpp_template_txt)    
        


    exit(0)

    def split_filename_bydot(file_name:str)->str:
        return file_name[:file_name.find('.')]
    
    def find_classname_inhfile(file_name:str)->str:
        with open(file_name,'r',encoding="utf-8") as f:
            for line in f.readlines():
                index = line.find("class")
                
                if index == -1:
                    continue
                index+=5
                end = index+1
                while line[end].isalpha():
                    end+=1
                return line[index+1:end]
                
    src_file_list = set(split_filename_bydot(file) for  file in os.listdir(src_dir))
    dst_file_list = set(split_filename_bydot(file) for  file in os.listdir(dst_dir))
    for include_file  in os.listdir(src_dir):
        print(include_file)
        with open(os.path.join(src_dir,include_file),"r+") as f:
            cache = f.readlines()
            if cache[0] == '\n':
                cache.pop(0)
            
            print(f.readlines())
            exit(0)
    print(src_file_list- dst_file_list)

    for copy_filename in src_file_list-dst_file_list:
        #print(copy_filename)
        class_name = find_classname_inhfile(os.path.join(src_dir,copy_filename)+".h")
        dst_file_path = os.path.join(dst_dir,copy_filename)+".cpp"
        with open(dst_file_path,"w") as f:
            cpp_template_txt = f"""#include "mindev/include/component/{copy_filename}.h"

namespace mindev::component{{
    int {class_name}::WireEncode(mindev::encoding::Encoder& encoder){{
        
        int totalLength = 0;
        std::vector<char> vec(this->value.begin(),this->value.end());
        int tmpLen = encoder.PrependByteArray(vec,mindev::encoding::SizeT(vec.size()));
        if(tmpLen<0){{
            return -1;
        }}
        totalLength += tmpLen;
        tmpLen = encoder.PrependVarNumber(mindev::encoding::VlInt(totalLength));
        if(tmpLen<0){{
            return -1;
        }}
        totalLength+=tmpLen;
        tmpLen = encoder.PrependVarNumber(this->tlvType);
        if(tmpLen<0){{
            return -1;
        }}
        totalLength+=tmpLen;
        return totalLength;
    }}
    bool {class_name}::WireDecode(mindev::encoding::Block& block){{
        this->tlvType = block.GetType();
        this->SetValue(std::string(block.GetValue().begin(),block.GetValue().end()));
        return true;
    }}
}}
"""
            f.write(cpp_template_txt)        
    #for src_filename in src_file_list:
    #    if src_filename!=
#    dir_name = "component"
    
    
#    copy_dir_name = "D:\min-dev-java-master\src\main\java\com\pkusz\mindev\component"
#    if os.path.exists(dir_name):
#        print("exists")
#    else:
#        os.mkdir(dir_name)
#        print(f"create dir {dir_name}")

#    for filename in os.listdir(copy_dir_name):
#        filename = filename[:filename.find('.')]
        
        
#        with open(os.path.join(dir_name,filename.lower()+'.h'),'w') as f:
#            h_template_txt = f"""
##ifndef {filename.upper()}_H_
##define {filename.upper()}_H_

#namespace mindev::{dir_name}{{
#    class {filename}{{

#    }};
#}}

##endif
#"""
#            f.write(h_template_txt)        
        
    