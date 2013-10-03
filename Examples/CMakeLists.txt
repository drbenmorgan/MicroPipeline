# - CMake script to build MicroPipeline experimental code
#
#-----------------------------------------------------------------------
# Poco
#
add_subdirectory(mp_asyncchannel)
add_subdirectory(mp_sharedlib)
add_subdirectory(mp_classloader)

#-----------------------------------------------------------------------
# TBB
#
add_subdirectory(tbb_pipeline)
add_subdirectory(tbb_queues)

