cmake_minimum_required(VERSION 3.6)
project(Core)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp include/MyTask.h ThreadPool/CoreThread.cpp ThreadPool/CoreThreadPool.cpp include/CoreLock.h ThreadPool/CoreLock.cpp include/ThreadContainer.h ThreadPool/ThreadContainer.cpp include/TaskQueue.h ThreadPool/TaskQueue.cpp include/TaskQueueContainer.h ThreadPool/TaskQueueContainer.cpp include/Common.h)
add_executable(Core ${SOURCE_FILES})