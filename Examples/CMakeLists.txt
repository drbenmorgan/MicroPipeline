# - CMake script to build MicroPipeline experimental code
#
include_directories(${POCO_INCLUDE_DIRS})

add_executable(mp_asyncchannel mp_asyncchannel.cpp)
target_link_libraries(mp_asyncchannel ${POCO_Foundation_LIBRARY})


