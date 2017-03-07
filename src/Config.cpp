//
// Created by cjn on 17-2-16.
//
#include <memory>
#include <cstring>
#include <vector>
#include <tuple>
#include <bits/ios_base.h>
#include <ios>
#include <istream>
#include <fstream>
#include "openssl/md5.h"
#include "openssl/pem.h"
#include "Config.h"
#include "HttpClient.h"

#include "LuaContext.hpp"
#include "json.hpp"
#include "minizip.h"

#define CONFIG_PACKAGE "config.zip"
#define CHECK_CONFIG_PREFIX_URL "http://192.168.0.252/ios/check"
#define GET_MODULE_PREFIX_URL "http://192.168.0.252/ios/getModule"

using namespace TBAS;
using namespace std;

Config Config::mConfig;

int TBAS::base64Encode(const char *str,int str_len,char *encode,int encode_len) {
    BIO *bmem,*b64;
    BUF_MEM *bptr;
    b64=BIO_new(BIO_f_base64());
    bmem=BIO_new(BIO_s_mem());
    b64=BIO_push(b64,bmem);
    BIO_write(b64,str,str_len); //encode
    BIO_flush(b64);
    BIO_get_mem_ptr(b64,&bptr);
    if(bptr->length>encode_len){
        LOGW("encode_len too small\n");
        return -1;
    }
    encode_len=bptr->length;
    memcpy(encode,bptr->data,bptr->length);
//  write(1,encode,bptr->length);
    BIO_free_all(b64);
    return encode_len;
}

int TBAS::base64Decode(const char *str,int str_len,char *decode,int decode_buffer_len) {
    int len=0;
    BIO *b64,*bmem;
    b64=BIO_new(BIO_f_base64());
    bmem=BIO_new_mem_buf(str,str_len);
    bmem=BIO_push(b64,bmem);
    len=BIO_read(bmem,decode,str_len);
    decode[len]=0;
    BIO_free_all(bmem);
    return len;
}

int TBAS::md5file(const std::string &file, unsigned char md5sum[16]) {
    FILE * fp = fopen(file.c_str(), "r");
    if (fp == nullptr) {
        // 文件不存在或没有权限
        return 1;
    }
    std::shared_ptr<FILE> sp(fp, fclose);

    MD5_CTX ctx;
    if (MD5_Init(&ctx) != 1) {
        return 2;
    }

    unsigned char buf[512];
    size_t len = 0;
    while ((len = fread(buf, 1, sizeof(buf), fp)) > 0) {
        if (MD5_Update(&ctx, buf, len) != 1) {
            MD5_Final(md5sum, &ctx);
            return 3;
        }
    }

    if (MD5_Final(md5sum, &ctx) != 1) {
        return 4;
    }

    return 0;
}

int TBAS::md5file(const std::string &file, string &md5string) {
    unsigned char md5[16];
    int ret = md5file(file, md5);
    if (ret != 0) {
        return ret;
    }

    char t[32+1];
    std::snprintf(t, sizeof(t), "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
                  md5[0], md5[1], md5[2],  md5[3],  md5[4],  md5[5],  md5[6],  md5[7],
                  md5[8], md5[9], md5[10], md5[11], md5[12], md5[13], md5[14], md5[15]);
    md5string = t;

    return 0;
}

bool TBAS::md5Check(const std::string &filename, const std::string &md5string) {
    if (md5string.empty()) {
        return false;
    }

    unsigned char md5hex[16];
    if (md5file(filename, md5hex) != 0) {
        return false;
    }

    char t[16];
    std::sscanf(md5string.c_str(), "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
           &t[0], &t[1], &t[2], &t[3], &t[4], &t[5], &t[6], &t[7],
           &t[8], &t[9], &t[10], &t[11], &t[12], &t[13], &t[14], &t[15]);

    return memcmp(md5hex, t, sizeof(md5hex))==0;
}

Config *Config::instance() { return &mConfig; }

int Config::loadConfig(const std::string &os, const std::string &version,
                        LuaContext *lua) {
    if (loadModule("config.lua", os, version, "", lua) != 0) {
        return Load_config_lua_failed;
    }

    try {
        char luacmd[100];
        snprintf(luacmd, sizeof(luacmd), "return #config.depend");
        int depend_size = lua->executeCode<int>(luacmd);
        for (int i=0; i<depend_size; i++) {
            snprintf(luacmd, sizeof(luacmd), "return config.depend[%d][1]", i+1);
            string mod = lua->executeCode<string>(luacmd);
            snprintf(luacmd, sizeof(luacmd), "return config.depend[%d][2]", i+1);
            string ver = lua->executeCode<string>(luacmd);
            snprintf(luacmd, sizeof(luacmd), "return config.depend[%d][3]", i+1);
            string md5 = lua->executeCode<string>(luacmd);

            if (loadModule(mod, os, ver, md5, lua) != 0) {
                LOGE("load %s failed\n", mod.c_str());
                return Load_module_lua_failed;
            }
            LOGD("load %s ok\n", mod.c_str());
        }

        snprintf(luacmd, sizeof(luacmd), "return #config.option");
        int option_size = lua->executeCode<int>(luacmd);
        for (int i=0; i<option_size; i++) {
            snprintf(luacmd, sizeof(luacmd), "return config.option[%d][1]", i+1);
            string mod = lua->executeCode<string>(luacmd);
            snprintf(luacmd, sizeof(luacmd), "return config.option[%d][2]", i+1);
            string ver = lua->executeCode<string>(luacmd);
            snprintf(luacmd, sizeof(luacmd), "return config.option[%d][3]", i+1);
            string md5 = lua->executeCode<string>(luacmd);

            if (loadModule(mod, os, ver, md5, lua) != 0) {
                LOGW("load %s failed\n", mod.c_str());
                continue;
            }
            LOGD("load %s ok\n", mod.c_str());
        }

        snprintf(luacmd, sizeof(luacmd), "return #config.cmdstring");
        int cmdstring_size = lua->executeCode<int>(luacmd);
        for (int i=0; i<cmdstring_size; i++) {
            snprintf(luacmd, sizeof(luacmd), "return config.cmdstring[%d][1]", i+1);
            string cmd = lua->executeCode<string>(luacmd);
            snprintf(luacmd, sizeof(luacmd), "return config.cmdstring[%d][2]", i+1);
            string fun = lua->executeCode<string>(luacmd);

            mCmdstring.insert(make_pair(cmd, fun));
        }
    } catch(const exception &e) {
        LOGE("load_config exception:%s\n", e.what());
        return Load_lua_exception;
    }
    LOGI("execute local_config_file ok\n");

    return Success;
}


int Config::loadModule(const std::string &module, const std::string &os, const std::string &version, const std::string &md5string,
                        LuaContext *lua) {
    auto iter = mLoadedModules.find(module);
    if (iter != mLoadedModules.end()) {
        if (version.empty()) {
            // 不用校验版本号
            return Success;
        }

        if (iter->second.compare(version) != 0) {
            LOGW("version loaded(%s) != loading(%s)\n", iter->second.c_str(), version.c_str());
            return Check_version_failed;
        }

        LOGI("already loaded %s\n", module.c_str());
        return Already_loaded;
    }

    char local_filename[256];
    snprintf(local_filename, sizeof(local_filename), "%s/%s", mConfigDir.c_str(), module.c_str());

    string local_filename_md5string;
    if (md5string.empty() ||
            (md5file(local_filename, local_filename_md5string) != 0) ||
            (md5string.compare(local_filename_md5string) != 0)) {
        // 本地md5校验失败，下载新版本
        char url[256];
        if (module.compare("config.lua") == 0) {
            // 下载config.zip
            snprintf(url, sizeof(url), CHECK_CONFIG_PREFIX_URL"?OS=%s&OSver=%s&Model=%s&APPver=%s&TBASver=%s&MD5=%s",
                mOS.c_str(), mOSver.c_str(), mModel.c_str(), mAPPver.c_str(), mTBASver.c_str(), md5string.c_str());
        } else {
            // 下载xx.lua
            snprintf(url, sizeof(url), GET_MODULE_PREFIX_URL"?OS=%s&OSver=%s&Model=%s&APPver=%s&TBASver=%s&FileName=%s",
                mOS.c_str(), mOSver.c_str(), mModel.c_str(), mAPPver.c_str(), mTBASver.c_str(), module.c_str());
        }

        string response;
        if (HttpClient::http_get(url, response) != 0) {
            LOGW("donwload %s failed\n", url);
            return Http_get_failed;
        }
        LOGI("download %s ok\n", url);

        if (module.compare("config.lua") == 0) {
            bool update = false;
            string config_base64;

            // json解码
            try {
                nlohmann::json j = nlohmann::json::parse(response.c_str());
                update = j["update"];
                if (update) {
                    config_base64 = j["config"];

                    // 空格转换\n
                    auto i = config_base64.find(' ');
                    while (i != string::npos) {
                        config_base64[i] = '\n';
                        i = config_base64.find(' ', i);
                    }
                }
            } catch (const exception &e) {
                LOGE("json parse exception:%s\n", e.what());
                return Parse_json_exception;
            }

            if (update) {
                // decode base64
                std::shared_ptr<char> config_bit(new char[config_base64.length()], std::default_delete<char[]>());
                int config_bit_len = base64Decode(config_base64.c_str(), config_base64.length(), config_bit.get(),
                                                   config_base64.length());

                // create config.zip
                char configzip_filename[256];
                snprintf(configzip_filename, sizeof(configzip_filename), "%s/%s", mConfigDir.c_str(), CONFIG_PACKAGE);
                FILE *fp = fopen(configzip_filename, "w+");
                if (fp == nullptr) {
                    LOGE("fopen %s failed:%s", configzip_filename, strerror(errno));
                    return Write_module_file_failed;
                }
                fwrite(config_bit.get(), 1, config_bit_len, fp);
                fclose(fp);

                // unzip config.zip
                char *argv[] = {"miniunz", "-x", "-o", configzip_filename};
                int ret = miniunz(4, argv);
                if (ret != 0) {
                    LOGE("miniunz %s failed:%d\n", configzip_filename, ret);
                    return Miniunz_failed;
                }

                // remove config.zip
                if (unlink(configzip_filename) != 0) {
                    LOGE("unlink %s failed:%s\n", configzip_filename, strerror(errno));
                } else {
                    LOGI("unlink %s ok\n", configzip_filename);
                }
            }
        } else {
            string md5;
            string file_base64;

            // json解码
            try {
                nlohmann::json j = nlohmann::json::parse(response.c_str());
                md5 = j["md5"];
                file_base64 = j["file"];

                // 空格转换\n
                auto i = file_base64.find(' ');
                    file_base64[i] = '\n';
                    i = file_base64.find(' ', i);
                    while (i != string::npos) {
                        file_base64[i] = '\n';
                        i = file_base64.find(' ', i);
                    }
            } catch (const exception &e) {
                LOGE("json parse exception:%s\n", e.what());
                return Parse_json_exception;
            }

            // decode base64
            std::shared_ptr<char> file_bit(new char[file_base64.length()], std::default_delete<char[]>());
            int file_bit_len = base64Decode(file_base64.c_str(), file_base64.length(), file_bit.get(),
                                               file_base64.length());

            // create module
            FILE *fp = fopen(local_filename, "w+");
            if (fp == nullptr) {
                LOGE("fopen %s failed:%s", local_filename, strerror(errno));
                return Write_module_file_failed;
            }
            fwrite(file_bit.get(), 1, file_bit_len, fp);
            fclose(fp);
        }

        // check md5
        if (!md5string.empty()) {
            if (!md5Check(local_filename, md5string)) {
                LOGE("checked md5 failed\n");
                return Check_md5_failed;
            }
            LOGI("checked md5 ok\n");
        }
    }

    try {
        // 加载模块
        std::ifstream ifs(local_filename);
        lua->executeCode(ifs);
        ifs.close();

        auto dot = module.rfind(".");
        string module_name = module.substr(0, dot);

        // 获取模块版本信息
        char luacmd[100];
        snprintf(luacmd, sizeof(luacmd), "return %s:version()", module_name.c_str());
        const auto config_version = lua->executeCode<tuple<string, string>>(luacmd);

        // 检查操作系统
        if (!os.empty()) {
            auto config_os = std::get<0>(config_version);
            if (config_os.compare("any") != 0) {
                if (config_os.compare(os) == 0) {
                    LOGI("checked %s os ok\n", module.c_str());
                } else {
                    LOGE("checked %s os failed\n", module.c_str());
                    unloadModule(module, lua);
                    return Check_os_failed;
                }
            }
        }

        // 检查版本
        if (!version.empty()) {
            auto config_ver = std::get<1>(config_version);
            if (config_ver.compare(version) == 0) {
                LOGI("checked %s version ok\n", module.c_str());
            } else {
                unloadModule(module, lua);
                LOGE("checked %s version failed\n", module.c_str());
                return Check_version_failed;
            }
        }
    } catch(const exception &e) {
        LOGE("load %s exception:%s\n", module.c_str(), e.what());
        return Load_module_lua_failed;
    }

    mLoadedModules.insert(make_pair(module, version));
    LOGI("execute %s ok\n", module.c_str());
    return Success;
}

int Config::unloadModule(const std::string &module, LuaContext *lua) {
    auto iter = mLoadedModules.find(module);
    if (iter != mLoadedModules.end()) {
        mLoadedModules.erase(iter);
    }

    try {
        char luacmd[50];
        snprintf(luacmd, sizeof(luacmd), "%s=nil", module.c_str());
        lua->executeCode(luacmd);
    } catch (const exception &e) {
        LOGE("unload exception:%s\n", e.what());
        return Unload_module_lua_failed;
    }
    LOGI("unload %s ok\n", module.c_str());

    return Success;
}

int Config::findFunction(const std::string &cmdstring, std::string &fun) {
    auto iter = mCmdstring.find(cmdstring);
    if (iter != mCmdstring.end()) {
        fun = iter->second;
        return Success;
    }
    return Not_found_function;
}
