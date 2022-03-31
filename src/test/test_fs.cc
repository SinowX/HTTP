//
// Created by Sinow on 2022/3/21.
//

#include "src/system/fs_wrap.h"
#include <iostream>


int main() {
    try {
//        auto fd = FS::Open("/home/sinow/", O_RDONLY);
        auto &&res = FS::ReadDirectory("/home/sinow/");
//        FS::Close(fd);
        for (auto &it: res) {
            std::cout << it.inode << "\n    " << it.name << std::endl;
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}