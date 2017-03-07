//
// Created by cjn on 17-2-16.
//

#include <memory>
#include "HttpClient.h"
#include "curl/curl.h"

using namespace TBAS;

int HttpClient::http_get_file(const std::string &src_url, const std::string &dst_local_file) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        return 1;
    }
    std::shared_ptr<CURL> spc(curl, curl_easy_cleanup);

    FILE *fp = fopen(dst_local_file.c_str(), "w+");
    if (!fp) {
        return 2;
    }
    std::shared_ptr<FILE> spf(fp, fclose);

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
//    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug);

    curl_easy_setopt(curl, CURLOPT_URL, src_url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
//    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
//    if(NULL == pCaPath)
//    {
//        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
//        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
//    }
//    else
//    {
//        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
//        curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);
//    }
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);

    auto res = curl_easy_perform(curl);
    if (res == CURLE_OK) {
        return 0;
    }
    return 3;
}

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *userdata) {
    ((std::string*)userdata)->append((char*)ptr, size * nmemb);
    return (size * nmemb);
}

int HttpClient::http_get(const std::string &src_url, std::string &data) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        return 1;
    }
    std::shared_ptr<CURL> spc(curl, curl_easy_cleanup);

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
//    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug);

    curl_easy_setopt(curl, CURLOPT_URL, src_url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
//    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
//    if(NULL == pCaPath)
//    {
//        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
//        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
//    }
//    else
//    {
//        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
//        curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);
//    }
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);

    auto res = curl_easy_perform(curl);
    if (res == CURLE_OK) {
        int http_code = 0;
        res = curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &http_code);
        if (res == CURLE_OK && http_code == 200) {
            return 0;
        }
    }
    return 3;
}
