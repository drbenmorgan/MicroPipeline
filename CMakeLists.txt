# - Top level CMake script for MicroPipeline
#
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(MicroPipeline)

#-----------------------------------------------------------------------
# Core setup
#
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)

#-----------------------------------------------------------------------
# Find required packages
#
find_package(Poco REQUIRED)
find_package(TBB REQUIRED)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#-----------------------------------------------------------------------
# Build the subcomponents
#
add_subdirectory(Source)
add_subdirectory(Examples)

#-----------------------------------------------------------------------
# Package...
#
include(CPack)

