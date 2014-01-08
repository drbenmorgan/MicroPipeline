# - Build script for libmagic examples
#
# - Dumb find of magic...
find_path(LibMagic_INCLUDE_DIR magic.h DOC "Path to LibMagic header")
find_library(LibMagic_LIBRARY magic DOC "Path to LibMagic library")

if(NOT LibMagic_INCLUDE_DIR OR NOT LibMagic_LIBRARY)
  message(STATUS "LibMagic not found, disabling libmagic example")
  return()
endif()

#-----------------------------------------------------------------------
# Continue if we have magic...
#
include_directories(${LibMagic_INCLUDE_DIR})
add_executable(basic_magic basic_magic.cc)
target_link_libraries(basic_magic ${LibMagic_LIBRARY})


