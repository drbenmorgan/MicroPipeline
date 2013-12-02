# - Find the Poco includes and libraries.
# The following variables are set if Poco is found.
#
# Poco_FOUND        - True when the Poco include directory is found.
# Poco_INCLUDE_DIRS - Path to where the poco include files are.
# Poco_LIBRARIES    - List of Poco libraries
#
# If your Poco installation is in a non-standard location, you can set
# Poco_ROOT to its installation prefix. This directory will be used
# to search first.

#-----------------------------------------------------------------------
# Copyright (c) 2013, Ben Morgan <bmorgan.warwick@gmail.com>
#
# Distributed under the OSI-approved BSD 3-Clause License (the "License");
# see accompanying file License.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#-----------------------------------------------------------------------

if(Poco_ROOT)
  set(Poco_HEADER_SEARCH PATHS ${Poco_ROOT}/include NO_SYSTEM_PATH)
  set(Poco_LIBRARY_SEARCH PATHS ${Poco_ROOT}/lib NO_SYSTEM_PATH)
endif()

# - Header path
find_path(Poco_INCLUDE_DIR Poco/Poco.h DOC "Path to Poco headers" ${Poco_HEADER_SEARCH})


# - Libraries in turn (only Foundation/Util for now, and don't
# distinguish Release/Debug)
find_library(Poco_FOUNDATION_LIBRARY
  NAMES PocoFoundation PocoFoundationd
  DOC "Path to Poco Foundation library"
  ${Poco_LIBRARY_SEARCH}
  )

find_library(Poco_UTIL_LIBRARY
  NAMES PocoUtil PocoUtild
  DOC "Path to Poco Utility library"
  ${Poco_LIBRARY_SEARCH}
  )

# - Handle Standard Args
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Poco DEFAULT_MSG Poco_INCLUDE_DIR Poco_FOUNDATION_LIBRARY)

if(POCO_FOUND)
  set(Poco_FOUND ${POCO_FOUND})
  set(Poco_INCLUDE_DIRS ${Poco_INCLUDE_DIR})
  set(Poco_LIBRARIES ${Poco_FOUNDATION_LIBRARY})
endif()

