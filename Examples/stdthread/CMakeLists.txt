# - Treat this as a separate project for now
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(stdthread)

# Force use of C++11 (not ideal, but haven't integrated try_compile of
# stdlib features yet)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Check threading headers?
include(CheckIncludeFileCXX)
check_include_file_cxx("thread" HAS_CXX_THREAD_H)
if(NOT HAS_CXX_THREAD_H)
  message(FATAL_ERROR "CXX does not provide a <thread> header")
endif()

check_include_file_cxx("future" HAS_CXX_FUTURE_H)
if(NOT HAS_CXX_FUTURE_H)
  message(FATAL_ERROR "CXX does not provide a <future> header")
endif()

check_include_file_cxx("mutex" HAS_CXX_MUTEX_H)
if(NOT HAS_CXX_MUTEX_H)
  message(FATAL_ERROR "CXX does not provide a <mutex> header")
endif()

check_include_file_cxx("condition_variable" HAS_CXX_CONDITION_H)

# add the example executables
add_executable(example_01 example_01.cpp)
add_executable(example_02 example_02.cpp)

