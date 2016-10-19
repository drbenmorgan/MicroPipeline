# - CMake script to build mp_asynchannel example
#
add_executable(mp_asyncchannel mp_asyncchannel.cpp)
target_link_libraries(mp_asyncchannel Poco::Foundation)

