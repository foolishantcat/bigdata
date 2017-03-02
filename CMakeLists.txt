cmake_minimum_required(VERSION 3.5)
project(Core)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(json/src)
include_directories(luawrapper/include)
include_directories(./)
include_directories(lua-5.3.4/src)

set(SOURCE_FILES
        main.cpp
		include/Scheduler.h
        Inteface/Scheduler.cpp
        include/MyTask.h
        ThreadPool/MyTask.cpp
		include/CoreThread.h
        ThreadPool/CoreThread.cpp
		include/CoreThreadPool.h
        ThreadPool/CoreThreadPool.cpp
        include/CoreLock.h
        ThreadPool/CoreLock.cpp
        include/ThreadContainer.h
        ThreadPool/ThreadContainer.cpp
        include/TaskQueue.h
        ThreadPool/TaskQueue.cpp
        include/TaskQueueContainer.h
        ThreadPool/TaskQueueContainer.cpp
        include/Common.h
        include/Semaphore.h)

link_directories("lua/lib/x86-64")

add_compile_options(-g)

add_executable(Core ${SOURCE_FILES})

target_link_libraries(Core liblua.a dl)
target_link_libraries(Core pthread)