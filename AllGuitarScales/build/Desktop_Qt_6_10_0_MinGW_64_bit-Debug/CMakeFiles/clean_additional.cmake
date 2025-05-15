# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "AllGuitarScales_autogen"
  "CMakeFiles\\AllGuitarScales_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AllGuitarScales_autogen.dir\\ParseCache.txt"
  )
endif()
