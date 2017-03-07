//
// Created by Benny.Zou on 16/7/21.
//

#ifndef _X_PLATFORMMACROS_H
#define _X_PLATFORMMACROS_H

/// @name namespace TBAS
#ifdef __cplusplus
#define NS_TBAS_BEGIN                     namespace TBAS {
#define NS_TBAS_END                       }
#define USING_NS_TBAS                     using namespace TBAS
#define TBAS_IM                           ::TBAS
#else
#define NS_TBAS_BEGIN
#define NS_TBAS_END
#define USING_NS_TBAS
#define TBAS_IM
#endif
//  end of namespace group

#ifdef __ANDROID__
#include <android/log.h>
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "TBAS", __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "TBAS", __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , "TBAS", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , "TBAS", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "TBAS", __VA_ARGS__)
#elseif __linux
#define LOGV(...) printf(__VA_ARGS__)
#define LOGD(...) printf(__VA_ARGS__)
#define LOGI(...) printf(__VA_ARGS__)
#define LOGW(...) printf(__VA_ARGS__)
#define LOGE(...) printf(__VA_ARGS__)
#elseif Win32
#define LOGV(...) printf(__VA_ARGS__)
#define LOGD(...) printf(__VA_ARGS__)
#define LOGI(...) printf(__VA_ARGS__)
#define LOGW(...) printf(__VA_ARGS__)
#define LOGE(...) printf(__VA_ARGS__)
#else
#define LOGV(...) printf(__VA_ARGS__)
#define LOGD(...) printf(__VA_ARGS__)
#define LOGI(...) printf(__VA_ARGS__)
#define LOGW(...) printf(__VA_ARGS__)
#define LOGE(...) printf(__VA_ARGS__)
#endif

#ifdef DEBUG
#define DLog(...) LOGD(__VA_ARGS__);
#else
#define DLog(...) {}
#endif

#endif //_X_PLATFORMMACROS_H
