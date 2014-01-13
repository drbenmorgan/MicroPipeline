# - Build script for libmagic examples
#
# - Dumb find of magic...
find_path(LibMagic_INCLUDE_DIR magic.h DOC "Path to LibMagic header")
find_library(LibMagic_LIBRARY magic DOC "Path to LibMagic library")

if(LibMagic_INCLUDE_DIR AND LibMagic_LIBRARY)
  set(LibMagic_FOUND 1)
endif()

# - CURL
find_package(CURL)

#-----------------------------------------------------------------------
# Continue if we have magic...
#
if(LibMagic_FOUND)
  include_directories(${LibMagic_INCLUDE_DIR})
  add_executable(basic_magic basic_magic.cc)
  target_link_libraries(basic_magic ${LibMagic_LIBRARY})
endif()

#-----------------------------------------------------------------------
# basic_curl if we have curl
#
if(CURL_FOUND)
  include_directories(${CURL_INCLUDE_DIRS})
  add_executable(basic_curl basic_curl.cc)
  target_link_libraries(basic_curl ${CURL_LIBRARIES})
endif()




