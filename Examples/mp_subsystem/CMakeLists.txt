# - CMake script to build MicroPipeline experimental code
#
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# - App
add_executable(mp_subsystem mp_subsystem.cpp
  MPSApplication.h
  MPSApplication.cpp
  )
target_link_libraries(mp_subsystem Poco::Util)

