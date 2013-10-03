# - CMake script to build MicroPipeline experimental code
#
include_directories(${TBB_INCLUDE_DIRS})

add_executable(mp_tbbpipeline tbb_pipeline.cpp)
target_link_libraries(mp_tbbpipeline ${TBB_LIBRARIES})

