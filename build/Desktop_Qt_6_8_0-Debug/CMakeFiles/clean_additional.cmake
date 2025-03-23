# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appAstraSpecs_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appAstraSpecs_autogen.dir/ParseCache.txt"
  "appAstraSpecs_autogen"
  )
endif()
