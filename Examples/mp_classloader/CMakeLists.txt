# - CMake script to build MicroPipeline experimental code
#
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# - App
add_executable(mp_classloader mp_classloader.cpp)
target_link_libraries(mp_classloader Poco::Foundation)

# - Library holding modules
add_library(MyProcessingModule MODULE
  MyProcessingModule/MyModuleFoo.cpp
  MyProcessingModule/MyModuleBar.cpp
  MyProcessingModule/PocoManifest.cpp
  )
target_link_libraries(MyProcessingModule Poco::Foundation)


