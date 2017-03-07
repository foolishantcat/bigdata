//
// Created by cjn on 17-2-16.
//

#ifndef _CONFIG_H
#define _CONFIG_H

#include "PlatformMacros.h"
#include <string>
#include <map>

class LuaContext;

namespace TBAS {
    class Config {
    public:
        static Config * instance();

        enum {
            Success = 0,
            Failed  = 1,
            Load_config_lua_failed,
            Load_module_lua_failed,
            Load_lua_exception,
            Http_get_failed,
            Parse_json_exception,
            Write_module_file_failed,
            Miniunz_failed,
            Check_md5_failed,
            Check_version_failed,
            Check_os_failed,
            Unload_module_lua_failed,
            Not_found_function,
            Already_loaded=100,
        };

        // 设置config文件目录
        void setConfigDir(const std::string &d) { mConfigDir = d; }

        // 设置系统环境信息
        // OS	操作系统，ios/android/windows
        // OSver	操作系统版本，例：6.0.1 MXB48T
        // Model	手机型号，大小写敏感，例：MI 5
        // APPver	应用版本，例：0.0.1
        // TBASver	TBAS版本，例：0.0.1
        void setVersion(std::string OS, std::string OSver, std::string Model, std::string APPver, std::string TBASver) {
            mOS = OS;
            mOSver = OSver;
            mModel = Model;
            mAPPver = APPver;
            mTBASver = TBASver;
        }

        // 加载config.lua及依赖脚本
        // os: 脚本配置的OS
        // version: 脚本配置的version
        // L: lua环境
        // return Success,Load_config_lua_failed,Load_module_lua_failed,Load_lua_exception
        int loadConfig(const std::string &os, const std::string &version, LuaContext *lua);

        // 加载模块
        // module：文件url，common.lua or common/json.lua
        // md5string：文件MD5校验,""则不校验
        // L: lua环境
        // return Success,
        int loadModule(const std::string &module, const std::string &os, const std::string &version,
                        const std::string &md5string, LuaContext *lua);

        // 卸载模块
        // return Success,Unload_module_lua_failed
        int unloadModule(const std::string &module, LuaContext *lua);

        // return Success,Failed
        int findFunction(const std::string &cmdstring, std::string &fun);

    private:
        Config() {}
        ~Config() {}

        std::string mConfigDir;
        std::string mOS, mOSver, mModel, mAPPver, mTBASver;

        // module_url->version
        std::map<std::string, std::string> mLoadedModules;

        std::map<std::string, std::string> mCmdstring;

        static Config mConfig;
    };

    // return encoded or decoded size
    int base64Encode(const char *str,int str_len,char *encode,int encode_len);
    int base64Decode(const char *str,int str_len,char *decode,int decode_buffer_len);

    // 计算文件的MD5
    // on success return 0, on error return >0
    int md5file(const std::string &file, unsigned char md5[16]);
    int md5file(const std::string &file, std::string &md5string);
    bool md5Check(const std::string &filename, const std::string &md5string);
}

#endif //_CONFIG_H
