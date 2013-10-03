# - CMake script to build MicroPipeline experimental code
#
include_directories(${TBB_INCLUDE_DIRS})

add_executable(mp_tbbqueues tbb_queues.cpp)
target_link_libraries(mp_tbbqueues ${TBB_LIBRARIES})

