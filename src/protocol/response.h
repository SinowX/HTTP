//
// Created by Sinow on 2022/3/29.
//

#ifndef SIHTTP_RESPONSE_H
#define SIHTTP_RESPONSE_H

#include <string>
#include <unordered_map>

namespace Status {

    // 用于在接收 response 的时候匹配打印信息
    std::unordered_map<uint16_t, std::string> CodeMap{
            {100, "Continue"},
            {101, "Switching Protocols"},
            {200, "OK"},
            {201, "Created"},
            {202, "Accepted"},
            {203, "Non-Authoritative Information"},
            {204, "No Content"},
            {205, "Reset Content"},
            {206, "Partial Content"},
            {300, "Multiple Choices"},
            {301, "Moved Permanently"},
            {302, "Found"},
            {303, "See Other"},
            {304, "Not Modified"},
            {305, "Use Proxy"},
            {307, "Temporary Redirect"},
            {400, "Bad Request"},
            {401, "Unauthorized"},
            {403, "Forbidden"},
            {404, "Not Found"},
            {405, "Method Not Allowed"},
            {406, "Not Acceptable"},
            {407, "Proxy Authentication Required"},
            {408, "Request Timeout"},
            {409, "Conflict"},
            {410, "Gone"},
            {411, "Length Required"},
            {412, "Precondition Failed"},
            {413, "Request Entity Too Large"},
            {414, "Request URL Too Long"},
            {415, "Unsupported Media Type"},
            {416, "Requested Range Not Satisfiable"},
            {417, "Expectation Failed"},
            {500, "Internal Server Error"},
            {501, "Not Implemented"},
            {502, "Bad Gateway"},
            {503, "Service Unavailable"},
            {504, "Gateway Timeout"},
            {505, "HTTP Version Not Supported"},
    };

    using Status = struct {
        uint16_t code;
        std::string info;
    };
    // 用于编写 response 时对应填写 status 和 reason phrase
    namespace Info {
        static Status Continue{100, "Continue"};
        static Status SwitchProtocol{101, "Switching Protocols"};
    }
    namespace Success {
        static Status OK{200, "OK"};
        static Status Created{201, "Created"};
        static Status Accepted{202, "Accepted"};
        static Status NoAuthInfo{203, "Non-Authoritative Information"};
        static Status NoContent{204, "No Content"};
        static Status ResetContent{205, "Reset Content"};
        static Status PartContent{206, "Partial Content"};
    }
    namespace Redirect {
        static Status MultiChoice{300, "Multiple Choices"};
        static Status Moved{301, "Moved Permanently"};
        static Status Found{302, "Found"};
        static Status SeeOther{303, "See Other"};
        static Status NotModified{304, "Not Modified"};
        static Status UseProxy{305, "Use Proxy"};
        static Status TempRedirect{307, "Temporary Redirect"};
    }
    namespace ClientFail {
        static Status BadRequest{400, "Bad Request"};
        static Status Unauthorized{401, "Unauthorized"};
//        reserved
//        static Status PaymentRequired{402,"Payment Required"};
        static Status Forbidden{403, "Forbidden"};
        static Status NotFound{404, "Not Found"};
        static Status MethodNotAllow{405, "Method Not Allowed"};
        static Status NotAcceptable{406, "Not Acceptable"};
        static Status UnauthorizedProxy{407, "Proxy Authentication Required"};
        static Status Timeout{408, "Request Timeout"};
        static Status Conflict{409, "Conflict"};
        static Status Gone{410, "Gone"};
        static Status LengthRequired{411, "Length Required"};
        static Status PreconditionFail{412, "Precondition Failed"};
        static Status RequestEntityTooLarge{413, "Request Entity Too Large"};
        static Status RequestUrlTooLong{414, "Request URL Too Long"};
        static Status UnsupportedMediaType{415, "Unsupported Media Type"};
        static Status RequestRangeFail{416, "Requested Range Not Satisfiable"};
        static Status ExpectationFail{417, "Expectation Failed"};
    }
    namespace ServerFail {
        static Status InternalServerError{500, "Internal Server Error"};
        static Status NotImplemented{501, "Not Implemented"};
        static Status BadGateway{502, "Bad Gateway"};
        static Status ServiceUnavailable{503, "Service Unavailable"};
        static Status GatewayTimeout{504, "Gateway Timeout"};
        static Status HttpVersionFail{505, "HTTP Version Not Supported"};
    }

}

#endif //SIHTTP_RESPONSE_H
