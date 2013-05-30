# - CMake script to build MicroPipeline experimental code
#
include_directories(${POCO_INCLUDE_DIRS})
include_directories(${TBB_INCLUDE_DIRS})

add_executable(mp_asyncchannel mp_asyncchannel.cpp)
target_link_libraries(mp_asyncchannel ${POCO_Foundation_LIBRARY})

add_executable(mp_sharedlib mp_sharedlib.cpp)
add_library(Foo MODULE Foo.cpp)
add_library(Bar SHARED Bar.cpp)
target_link_libraries(mp_sharedlib ${POCO_Foundation_LIBRARY})

add_executable(mp_tbbpipeline tbb_pipeline.cpp)
target_link_libraries(mp_tbbpipeline ${TBB_LIBRARIES})

