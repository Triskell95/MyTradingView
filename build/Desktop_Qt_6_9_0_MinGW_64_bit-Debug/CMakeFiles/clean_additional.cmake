# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MyTradingView_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MyTradingView_autogen.dir\\ParseCache.txt"
  "MyTradingView_autogen"
  )
endif()
