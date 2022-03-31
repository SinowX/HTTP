//
// Created by Sinow on 2022/3/30.
//

#ifndef SIHTTP_WORKER_H
#define SIHTTP_WORKER_H

#include "network/tcp_wrap.h"
#include "protocol/request_parser.h"

class Worker {
private:
    FD _fd;
    RequestParser _rqs_parser{};

    std::string ReadMeta(int fd) {
        std::string res{};

        return res;
    }



public:
    Worker(FD &&fd) : _fd(std::move(fd)) {}

    Worker(Worker const &) = delete;

    Worker(Worker &&) = delete;

    void Run() {
        while(true) {
            _rqs_parser.Parse(ReadMeta(_fd.Get()));


        }
    }
};


#endif //SIHTTP_WORKER_H