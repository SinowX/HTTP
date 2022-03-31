//
// Created by Sinow on 2022/3/21.
//

#include <iostream>
#include "src/system/fd_wrap.h"

int main() {
    int fd = open("/home/sinow/diffs", O_RDONLY);
    if(fd==-1)
    {
        std::cout<<strerror(errno)<<std::endl;
        abort();
    }
    try {
        FD obj(fd);
        std::cout<<obj.GetAsyncSigOwner()<<std::endl;


    } catch (std::exception& e) {
        std::cout<<e.what()<<std::endl;
    }

}
