# - CMake script to build MicroPipeline experimental code
#
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# - App
add_executable(mp_sharedlib mp_sharedlib.cpp)
target_link_libraries(mp_sharedlib Poco::Foundation)

# - Plugins
add_library(Foo MODULE Foo.cpp)
add_library(Bar SHARED Bar.cpp)


