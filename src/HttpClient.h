//
// Created by cjn on 17-2-16.
//

#ifndef _HTTPCLIENT_H
#define _HTTPCLIENT_H

#include <string>

namespace TBAS {
    class HttpClient {
    public:
        // 同步调用
        static int http_get_file(const std::string &src_url, const std::string &dst_local_file);
        static int http_get(const std::string &src_url, std::string &data);
    };
}

#endif //_HTTPCLIENT_H
