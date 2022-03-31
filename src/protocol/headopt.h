//
// Created by Sinow on 2022/3/29.
//

#ifndef SIHTTP_HEADOPT_H
#define SIHTTP_HEADOPT_H

#include <iostream>

namespace Header {
    using Header = struct {
        std::string const key;
        std::string value;
    };
    namespace General {
        static Header Connection{"Connection", {}};
        static Header Date{"Date", {}};
        static Header MIME_Version{"MIME-Version", {}};
        static Header Trailer{"Trailer", {}};
        static Header Transfer_Encoding{"Transfer-Encoding", {}};
        static Header Update{"Update", {}};
        static Header Via{"Via", {}};
        static Header Cache_Control{"Cache-Control", {}};
        static Header Pragma{"Pragma", {}};
    }

    namespace Request {
        static Header Client_IP{"Client-IP", {}};
        static Header From{"From", {}};
        static Header Host{"Host", {}};
        static Header Referer{"Referer", {}};
        static Header UA_Color{"UA-Color", {}};
        static Header UA_CPU{"UA-CPU", {}};
        static Header UA_Disp{"UA-Disp", {}};
        static Header UA_OS{"UA-OS", {}};
        static Header UA_Pixels{"UA-Pixels", {}};
        static Header User_Agent{"User-Agent", {}};
        static Header Accept{"Accept", {}};
        static Header Accept_Charset{"Accept-Charset", {}};
        static Header Accept_Encoding{"Accept-Encoding", {}};
        static Header Accept_Language{"Accept-Language", {}};
        static Header TE{"TE", {}};
        static Header Expect{"Expect", {}};
        static Header If_Match{"If-Match", {}};
        static Header If_Modified_Since{"If-Modified-Since", {}};
        static Header If_None_Match{"If-None-Match", {}};
        static Header If_Range{"If-Range", {}};
        static Header If_Unmodified_Sinc{"If-Unmodified-Sinc", {}};
        static Header Range{"Range", {}};
        static Header Authorization{"Authorization", {}};
        static Header Cookie{"Cookie", {}};
        static Header Cookie2{"Cookie2", {}};
        static Header Max_Forward{"Max-Forward", {}};
        static Header Proxy_Authorizatio{"Proxy-Authorizatio", {}};
        static Header Proxy_Connection{"Proxy-Connection", {}};
    }

    namespace Response {
        static Header Age{"Age", {}};
        static Header Public{"Public", {}};
        static Header Retry_After{"Retry-After", {}};
        static Header Server{"Server", {}};
        static Header Title{"Title", {}};
        static Header Warning{"Warning", {}};
        static Header Accept_Ranges{"Accept-Ranges", {}};
        static Header Vary{"Vary", {}};
        static Header Proxy_Authenticate{"Proxy-Authenticate", {}};
        static Header Set_Cookie{"Set-Cookie", {}};
        static Header Set_Cookie2{"Set-Cookie2", {}};
        static Header WWW_Authenticate{"WWW-Authenticate", {}};
    }

    namespace Entity {
        static Header Allow{"Allow", {}};
        static Header Location{"Location", {}};
        static Header Content_Base{"Content-Base", {}};
        static Header Content_Encoding{"Content-Encoding", {}};
        static Header Content_Language{"Content-Language", {}};
        static Header Content_Length{"Content-Length", {}};
        static Header Content_Location{"Content-Location", {}};
        static Header Content_MD5{"Content-MD5", {}};
        static Header Content_Range{"Content-Range", {}};
        static Header Content_Type{"Content-Type", {}};
        static Header ETag{"ETag", {}};
        static Header Expires{"Expires", {}};
        static Header Last_Modified{"Last-Modified", {}};
    }
}

#endif //SIHTTP_HEADOPT_H
