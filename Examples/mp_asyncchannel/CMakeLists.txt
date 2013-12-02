# - CMake script to build mp_asynchannel example
#
include_directories(${Poco_INCLUDE_DIRS})
add_executable(mp_asyncchannel mp_asyncchannel.cpp)
target_link_libraries(mp_asyncchannel ${Poco_FOUNDATION_LIBRARY})

