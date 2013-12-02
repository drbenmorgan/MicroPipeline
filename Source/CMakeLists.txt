# - CMake script for main MicroPipeline application
#
#-----------------------------------------------------------------------
# Copyright 2013 Ben Morgan <bmorgan.warwick@gmail.com>
# Copyright 2013 University of Warwick
#
# Distributed under the OSI-approved BSD 3-Clause License (the "License");
# see accompanying file License.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#-----------------------------------------------------------------------

include_directories(${Poco_INCLUDE_DIRS})
add_executable(micro_pipeline micro_pipeline.cpp)
target_link_libraries(micro_pipeline ${Poco_FOUNDATION_LIBRARY} ${Poco_UTIL_LIBRARY})

