//
// Created by Sinow on 2022/3/30.
//

#ifndef SIHTTP_STORAGE_MAP_H
#define SIHTTP_STORAGE_MAP_H

#include "system/fs_wrap.h"

// support path type:
// '/foo/bar': bar can be file or directory
// '/foo/bar/': bar is a directory
// 'foo'
// StorageMap is an interface, providing filesystem access utilities
// What it can do are listed below
// 1. convert valid urls to standard path
// 2. scan a directory, return what it contains
namespace Storage {

    enum class FileType : uint8_t {
        BLOCK,
        CHAR,
        DIR,
        FIFO,
        LINK,
        REGULAR,
        SOCKET,
        UNKNOWN,
    };

    using DirEntry = struct {
        ino64_t Inode{};
        FileType Type{};
        std::string Name{};
    };

// convert multiple style path to a standard path
// standard is an absolute path from root to resource
// relative path will be based on current working directory
    std::string makeStdPath(std::string const &path);


}


#endif //SIHTTP_STORAGE_MAP_H
