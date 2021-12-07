cmake_minimum_required (VERSION 3.8)

#link:https://stackoverflow.com/questions/1662909/undefined-reference-to-pthread-create-in-linux
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

include_directories("../asio-1.20.0_include/")

# add_executable (PixelFPSServer "PixelFPSServer.cpp" "PixelFPSServer.h")

add_executable (PixelFPSServer "PixelFPSServerDemo.cpp" "PixelFPSServer.h")