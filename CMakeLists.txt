# - Top level CMake script for MicroPipeline
#
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(MicroPipeline)

#-----------------------------------------------------------------------
# Find required packages
#
# find_package(POCO REQUIRED) // For later, hand set for now...
find_path(POCO_INCLUDE_DIR Poco/Foundation.h)
find_library(POCO_Foundation_LIBRARY NAMES PocoFoundation)
find_library(POCO_Util_LIBRARY NAMES PocoUtil)
set(POCO_INCLUDE_DIRS ${POCO_INCLUDE_DIR})
set(POCO_LIBRARIES ${POCO_Foundation_LIBRARY} ${POCO_Util_LIBRARY})

# find_package(TBB REQUIRED) // For later, hand set for now...
find_path(TBB_INCLUDE_DIR tbb/tbb.h)
find_library(TBB_LIBRARY NAMES tbb)
find_library(TBB_MALLOC_LIBRARY NAMES tbbmalloc)
set(TBB_INCLUDE_DIRS ${TBB_INCLUDE_DIR} ${TBB_INCLUDE_DIR}/tbb)
set(TBB_LIBRARIES ${TBB_LIBRARY} ${TBB_MALLOC_LIBRARY})

#-----------------------------------------------------------------------
# Build the subcomponents
#
add_subdirectory(Source)
add_subdirectory(Examples)

#-----------------------------------------------------------------------
# Package...
#
include(CPack)

