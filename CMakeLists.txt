cmake_minimum_required(VERSION 3.27)
project(concorde)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.h)
add_executable(concorde ${SRC_FILES})

set_property(TARGET concorde PROPERTY CXX_STANDARD 20)
