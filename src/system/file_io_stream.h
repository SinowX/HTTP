//
// Created by Sinow on 2022/3/30.
//

#ifndef SIHTTP_FILE_IO_STREAM_H
#define SIHTTP_FILE_IO_STREAM_H

#include "system/io_stream.h"

// 涉及syscall
// lseek() read() write() pread() pwrite() sync() fsync() fdatasync() fcntl() ioctl()
class FileStream : IOStream {

};

#endif //SIHTTP_FILE_IO_STREAM_H
