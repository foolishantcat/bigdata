cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/zlib/include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/zlib/lib/x86-64)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/openssl/include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/openssl/lib/x86-64)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/json)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/libcurl/include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/libcurl/lib/x86-64)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/luawrapper)
#INCLUDE_DIRECTORIES(3rdpart/lua/include)
#LINK_DIRECTORIES(3rdpart/lua/lib/x86-64)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/luajit-2.0/include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/luajit/lib/x86-64)

set(SOURCE_FILES Config.cpp Config.h HttpClient.cpp HttpClient.h
        CScheduler.h
        CScheduler.cpp
        CMyTask.h
        CMyTask.cpp
        CTaskThread.h
        CTaskThread.cpp
        CMessageThread.h
        CMessageThread.cpp
        Global.h
        CSemaphore.h
        IASObject.h)
add_library(tbas_core STATIC ${SOURCE_FILES})
#TARGET_LINK_LIBRARIES(tbas_core luajit-5.1 curl minizip z ssl crypto dl pthread)
TARGET_LINK_LIBRARIES(tbas_core)
