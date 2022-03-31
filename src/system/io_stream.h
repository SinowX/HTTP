//
// Created by Sinow on 2022/3/30.
//

#ifndef SIHTTP_IOSTREAM_H
#define SIHTTP_IOSTREAM_H

#include "system/file_descriptor.h"
#include <vector>
#include <limits>
#include <memory>


enum class LSeekBase {
    BEGIN,
    CUR,
    END
};

// IOStream作为 pure virtual class，提供IO的统一交互模式
class IOStream {
private:
    std::unique_ptr<FileDescriptor> _fd;

public:
    explicit IOStream(std::unique_ptr<FileDescriptor> &&fd) : _fd(std::move(fd)) {}

    std::unique_ptr<FileDescriptor> const &GetFd() { return _fd; }

    // read result return as std::vector<char>
    // dev other than filesystem ignore offset
    virtual std::vector<char> Read(std::size_t max_len = std::numeric_limits<std::size_t>::max(),
                                   off_t offset = std::numeric_limits<off_t>::max()) = 0;

    // return success write
    // dev other than filesystem ignore offset
    virtual std::size_t Write(std::vector<char> const &data, off_t offset = std::numeric_limits<off_t>::max()) = 0;

    // return success write
    // dev other than filesystem ignore offset
    virtual std::size_t Write(std::vector<char> const &data, std::vector<char>::iterator begin,
                              off_t offset = std::numeric_limits<off_t>::max()) = 0;


public:
    // only work for file stream
    // flush kernel buffer
    // relative syscall: sync() fsync() fdatasync()
    virtual void Flush() = 0;

    // only work for file stream
    // modify offset
    virtual off_t LSeek(off_t offset, LSeekBase start = LSeekBase::BEGIN);

};


#endif
