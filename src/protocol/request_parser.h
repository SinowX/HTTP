//
// Created by Sinow on 2022/3/29.
//

#ifndef SIHTTP_REQUEST_PARSER_H
#define SIHTTP_REQUEST_PARSER_H

#include "protocol/request.h"
#include <vector>
#include <tuple>

class RequestParser {
private:

    std::unordered_map<std::string, std::string> _headers{};
    std::string _method{};
    std::string _request_url{};
    std::string _version{};

    void Reset() {
        _headers.clear();
        _method.clear();
        _request_url.clear();
        _version.clear();
    }

public:

    void Parse(std::string const &meta_info);

    auto getMethod() const { return _method; }

    auto getRequestURL() const { return _request_url; }

    auto getVersion() const { return _version; }

};

#endif //SIHTTP_REQUEST_PARSER_H
