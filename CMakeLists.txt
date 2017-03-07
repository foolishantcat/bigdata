cmake_minimum_required(VERSION 3.5)
project(main)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_subdirectory(src)

INCLUDE_DIRECTORIES(src)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/zlib/lib/x86-64)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/openssl/lib/x86-64)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/libcurl/lib/x86-64)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/luawrapper)
#INCLUDE_DIRECTORIES(3rdpart/lua/include)
#LINK_DIRECTORIES(3rdpart/lua/lib/x86-64)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/luajit-2.0/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/json)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdpart/luajit/lib/x86-64)

set(SOURCE_FILES main.cpp)
add_executable(main ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(main tbas_core luajit-5.1 curl minizip z ssl crypto dl pthread)