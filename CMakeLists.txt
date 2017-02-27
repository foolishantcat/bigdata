cmake_minimum_required(VERSION 3.6)
project(Core)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp include/MyTask.h ThreadPool/CoreThread.cpp ThreadPool/CoreThreadPool.cpp ThreadPool/SchedulerGarbo.cpp include/CoreLock.h ThreadPool/CoreLock.cpp include/ThreadContainer.h ThreadPool/ThreadContainer.cpp include/ObjectContainer.h ThreadPool/ObjectContainer.cpp)
add_executable(Core ${SOURCE_FILES})