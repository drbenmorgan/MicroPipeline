# - CMake script to build mp_asynchannel example
#
include_directories(${POCO_INCLUDE_DIRS})
add_executable(mp_asyncchannel mp_asyncchannel.cpp)
target_link_libraries(mp_asyncchannel ${POCO_Foundation_LIBRARY})

