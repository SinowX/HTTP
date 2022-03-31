//
// Created by Sinow on 2022/3/29.
//

#ifndef SIHTTP_RESPONSE_PARSER_H
#define SIHTTP_RESPONSE_PARSER_H

#include "protocol/response.h"
#include <unordered_map>
#include <tuple>

class ResponseParser {
private:

    std::unordered_map<std::string, std::string> _headers{};
    std::string _version{};
    uint16_t _status{};

    void Reset() {
        _headers.clear();
        _version.clear();
        _status = 0;
    }

public:

    void Parse(std::string const &meta_info);

    auto getStatus() const { return _status; }

    auto getVersion() const { return _version; }

};


#endif //SIHTTP_RESPONSE_PARSER_H
