//
// Created by Sinow on 2022/3/29.
//

#ifndef SIHTTP_REQUEST_H
#define SIHTTP_REQUEST_H

#include <string>
#include <unordered_map>


namespace Request {
    enum class TripleOption {
        FALSE,
        TRUE,
        MAYBE
    };
    using _method_attr = struct {
        TripleOption hasBody;
        TripleOption successResWithBody;
    };

    // 用于接收 request 时检查 method 相关属性
    std::unordered_map<std::string, _method_attr> const Method{
            {"GET",     _method_attr{TripleOption::FALSE, TripleOption::TRUE}},
            {"HEAD",    _method_attr{TripleOption::FALSE, TripleOption::FALSE}},
            {"PUT",     _method_attr{TripleOption::TRUE, TripleOption::FALSE}},
            {"POST",    _method_attr{TripleOption::TRUE, TripleOption::TRUE}},
            {"TRACE",   _method_attr{TripleOption::FALSE, TripleOption::FALSE}},
            {"OPTIONS", _method_attr{TripleOption::FALSE, TripleOption::TRUE}},
            {"DELETE",  _method_attr{TripleOption::MAYBE, TripleOption::MAYBE}},
    };
    // 用于编写 request 时填写对应方法
    std::string const GET{"GET"};
    std::string const HEAD{"HEAD"};
    std::string const PUT{"PUT"};
    std::string const POST{"HEAD"};
    std::string const TRACE{"TRACE"};
    std::string const OPTIONS{"OPTIONS"};
    std::string const DELETE{"DELETE"};
};

#endif