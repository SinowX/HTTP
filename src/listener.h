//
// Created by Sinow on 2022/3/30.
//

#ifndef SIHTTP_LISTENER_H
#define SIHTTP_LISTENER_H

#include "config_manager.h"
#include "network/tcp_wrap.h"
#include <map>
#include <memory>

class Listener {
private:
    TCP _tcp;
    std::map<std::string, FD> _map;
    SocketAddress _sock_address;
public:
    Listener()
            : _tcp(Config().getListenAddress(), Config().getListenPort()),
              _map() {
        _tcp.Listen();
    }

    [[noreturn]]  void Run() {

        struct sockaddr_in addr{};
        socklen_t addr_len{sizeof(addr)};
        char ipv4_dot_addr[16]{0};

        while (true) {
            auto newClient = _tcp.Accept();
            if (getpeername(newClient.Get(), reinterpret_cast<struct sockaddr *>(&addr), &addr_len) == -1)
                throw std::runtime_error("getpeername() failed");
            std::string key(inet_ntoa(addr.sin_addr));
            key.append(":" + std::to_string(ntohs(addr.sin_port)));
            if(_map.find(key)==_map.end()) {
                _map[key] = std::move(newClient);
                // start new thread
            }
            // 如果该Client已经建立连接，则不处理
        }
    }


};


#endif //SIHTTP_LISTENER_H
