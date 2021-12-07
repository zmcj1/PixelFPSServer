cmake_minimum_required (VERSION 3.8)

add_executable (PixelFPSServer "PixelFPSServer.cpp" "PixelFPSServer.h")

include_directories("../asio-1.20.0_include/")

# link:https://stackoverflow.com/questions/1620918/cmake-and-libpthread
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -pthread")