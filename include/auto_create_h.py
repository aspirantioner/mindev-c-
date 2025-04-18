import os

if __name__ == "__main__":
    dir_name = "component"
    
    
    copy_dir_name = "D:\min-dev-java-master\src\main\java\com\pkusz\mindev\component"
    if os.path.exists(dir_name):
        print("exists")
    else:
        os.mkdir(dir_name)
        print(f"create dir {dir_name}")

    for filename in os.listdir(copy_dir_name):
        filename = filename[:filename.find('.')]
        
        
        with open(os.path.join(dir_name,filename.lower()+'.h'),'w') as f:
            h_template_txt = f"""
#ifndef {filename.upper()}_H_
#define {filename.upper()}_H_

namespace mindev::{dir_name}{{
    class {filename}{{

    }};
}}

#endif
"""
            f.write(h_template_txt)        
        
    