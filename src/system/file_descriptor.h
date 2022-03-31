//
// Created by Sinow on 2022/3/30.
//

#ifndef SIHTTP_FILE_DESCRIPTOR_H
#define SIHTTP_FILE_DESCRIPTOR_H

// std::move()
#include <utility>
// close()
#include <unistd.h>

// FileDescriptor 管理fd的生存周期并提供修改flags的接口，Non-Copyable, Movable Only
// 不提供线程安全，可额外使用 mutex 或 unique_ptr 等机制实现线程安全
class FileDescriptor {
private:
    int _fd;

public:
    int Get() const { return _fd; }

    // fd Manipulation with fcntl()
    // so many fcntl() functionalities to exploit, remember to do it !!! :(
public:
    // if target specified, then use dup2(), else use fcntl(F_DUPFD_CLOEXEC)
    int Dup(int target = -1);

    // set O_RDONLY
    int setModeRD();

    // set O_WRONLY
    int setModeWR();

    // set O_RDWR
    int setModeRW();

    // set O_APPEND
    int setAppend();

    // set O_ASYNC
    int setAsync();

    // set O_DIRECT
    int setDirect();

    // set O_NOATIME
    int setNoAccessTime();

    // set O_NONBLOCK
    int setNonBlock();

public:
    explicit FileDescriptor(int fd) : _fd(fd) {}

    FileDescriptor(FileDescriptor const &) = delete;

    void operator=(FileDescriptor const &) = delete;

    FileDescriptor(FileDescriptor &&obj) noexcept {
        _fd = obj._fd;
        obj._fd = -1;
    }

    FileDescriptor &operator=(FileDescriptor &&obj) noexcept {
        auto tmp = FileDescriptor(std::move(obj));
        std::swap(*this, tmp);
        return *this;
    }

    virtual ~FileDescriptor() {
        close(_fd);
    }

};

#endif //SIHTTP_FILE_DESCRIPTOR_H