# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cyc/Core

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cyc/Core

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/cyc/Core/CMakeFiles /home/cyc/Core/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/cyc/Core/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Core

# Build rule for target.
Core: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Core
.PHONY : Core

# fast build rule for target.
Core/fast:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/build
.PHONY : Core/fast

ThreadPool/CoreLock.o: ThreadPool/CoreLock.cpp.o

.PHONY : ThreadPool/CoreLock.o

# target to build an object file
ThreadPool/CoreLock.cpp.o:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/CoreLock.cpp.o
.PHONY : ThreadPool/CoreLock.cpp.o

ThreadPool/CoreLock.i: ThreadPool/CoreLock.cpp.i

.PHONY : ThreadPool/CoreLock.i

# target to preprocess a source file
ThreadPool/CoreLock.cpp.i:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/CoreLock.cpp.i
.PHONY : ThreadPool/CoreLock.cpp.i

ThreadPool/CoreLock.s: ThreadPool/CoreLock.cpp.s

.PHONY : ThreadPool/CoreLock.s

# target to generate assembly for a file
ThreadPool/CoreLock.cpp.s:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/CoreLock.cpp.s
.PHONY : ThreadPool/CoreLock.cpp.s

ThreadPool/CoreThread.o: ThreadPool/CoreThread.cpp.o

.PHONY : ThreadPool/CoreThread.o

# target to build an object file
ThreadPool/CoreThread.cpp.o:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/CoreThread.cpp.o
.PHONY : ThreadPool/CoreThread.cpp.o

ThreadPool/CoreThread.i: ThreadPool/CoreThread.cpp.i

.PHONY : ThreadPool/CoreThread.i

# target to preprocess a source file
ThreadPool/CoreThread.cpp.i:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/CoreThread.cpp.i
.PHONY : ThreadPool/CoreThread.cpp.i

ThreadPool/CoreThread.s: ThreadPool/CoreThread.cpp.s

.PHONY : ThreadPool/CoreThread.s

# target to generate assembly for a file
ThreadPool/CoreThread.cpp.s:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/CoreThread.cpp.s
.PHONY : ThreadPool/CoreThread.cpp.s

ThreadPool/CoreThreadPool.o: ThreadPool/CoreThreadPool.cpp.o

.PHONY : ThreadPool/CoreThreadPool.o

# target to build an object file
ThreadPool/CoreThreadPool.cpp.o:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/CoreThreadPool.cpp.o
.PHONY : ThreadPool/CoreThreadPool.cpp.o

ThreadPool/CoreThreadPool.i: ThreadPool/CoreThreadPool.cpp.i

.PHONY : ThreadPool/CoreThreadPool.i

# target to preprocess a source file
ThreadPool/CoreThreadPool.cpp.i:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/CoreThreadPool.cpp.i
.PHONY : ThreadPool/CoreThreadPool.cpp.i

ThreadPool/CoreThreadPool.s: ThreadPool/CoreThreadPool.cpp.s

.PHONY : ThreadPool/CoreThreadPool.s

# target to generate assembly for a file
ThreadPool/CoreThreadPool.cpp.s:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/CoreThreadPool.cpp.s
.PHONY : ThreadPool/CoreThreadPool.cpp.s

ThreadPool/TaskQueue.o: ThreadPool/TaskQueue.cpp.o

.PHONY : ThreadPool/TaskQueue.o

# target to build an object file
ThreadPool/TaskQueue.cpp.o:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/TaskQueue.cpp.o
.PHONY : ThreadPool/TaskQueue.cpp.o

ThreadPool/TaskQueue.i: ThreadPool/TaskQueue.cpp.i

.PHONY : ThreadPool/TaskQueue.i

# target to preprocess a source file
ThreadPool/TaskQueue.cpp.i:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/TaskQueue.cpp.i
.PHONY : ThreadPool/TaskQueue.cpp.i

ThreadPool/TaskQueue.s: ThreadPool/TaskQueue.cpp.s

.PHONY : ThreadPool/TaskQueue.s

# target to generate assembly for a file
ThreadPool/TaskQueue.cpp.s:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/TaskQueue.cpp.s
.PHONY : ThreadPool/TaskQueue.cpp.s

ThreadPool/TaskQueueContainer.o: ThreadPool/TaskQueueContainer.cpp.o

.PHONY : ThreadPool/TaskQueueContainer.o

# target to build an object file
ThreadPool/TaskQueueContainer.cpp.o:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/TaskQueueContainer.cpp.o
.PHONY : ThreadPool/TaskQueueContainer.cpp.o

ThreadPool/TaskQueueContainer.i: ThreadPool/TaskQueueContainer.cpp.i

.PHONY : ThreadPool/TaskQueueContainer.i

# target to preprocess a source file
ThreadPool/TaskQueueContainer.cpp.i:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/TaskQueueContainer.cpp.i
.PHONY : ThreadPool/TaskQueueContainer.cpp.i

ThreadPool/TaskQueueContainer.s: ThreadPool/TaskQueueContainer.cpp.s

.PHONY : ThreadPool/TaskQueueContainer.s

# target to generate assembly for a file
ThreadPool/TaskQueueContainer.cpp.s:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/TaskQueueContainer.cpp.s
.PHONY : ThreadPool/TaskQueueContainer.cpp.s

ThreadPool/ThreadContainer.o: ThreadPool/ThreadContainer.cpp.o

.PHONY : ThreadPool/ThreadContainer.o

# target to build an object file
ThreadPool/ThreadContainer.cpp.o:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/ThreadContainer.cpp.o
.PHONY : ThreadPool/ThreadContainer.cpp.o

ThreadPool/ThreadContainer.i: ThreadPool/ThreadContainer.cpp.i

.PHONY : ThreadPool/ThreadContainer.i

# target to preprocess a source file
ThreadPool/ThreadContainer.cpp.i:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/ThreadContainer.cpp.i
.PHONY : ThreadPool/ThreadContainer.cpp.i

ThreadPool/ThreadContainer.s: ThreadPool/ThreadContainer.cpp.s

.PHONY : ThreadPool/ThreadContainer.s

# target to generate assembly for a file
ThreadPool/ThreadContainer.cpp.s:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/ThreadPool/ThreadContainer.cpp.s
.PHONY : ThreadPool/ThreadContainer.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Core"
	@echo "... ThreadPool/CoreLock.o"
	@echo "... ThreadPool/CoreLock.i"
	@echo "... ThreadPool/CoreLock.s"
	@echo "... ThreadPool/CoreThread.o"
	@echo "... ThreadPool/CoreThread.i"
	@echo "... ThreadPool/CoreThread.s"
	@echo "... ThreadPool/CoreThreadPool.o"
	@echo "... ThreadPool/CoreThreadPool.i"
	@echo "... ThreadPool/CoreThreadPool.s"
	@echo "... ThreadPool/TaskQueue.o"
	@echo "... ThreadPool/TaskQueue.i"
	@echo "... ThreadPool/TaskQueue.s"
	@echo "... ThreadPool/TaskQueueContainer.o"
	@echo "... ThreadPool/TaskQueueContainer.i"
	@echo "... ThreadPool/TaskQueueContainer.s"
	@echo "... ThreadPool/ThreadContainer.o"
	@echo "... ThreadPool/ThreadContainer.i"
	@echo "... ThreadPool/ThreadContainer.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
