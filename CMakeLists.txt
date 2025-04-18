cmake_minimum_required(VERSION 3.27)
project(concorde)

# C++20 Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Collect source files (excluding tests)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.h)

foreach(file ${SRC_FILES})
    if(file MATCHES ".test.cpp$")
        list(REMOVE_ITEM SRC_FILES ${file})
    endif()
endforeach()

add_executable(concorde ${SRC_FILES})


# --- GoogleTest setup ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/155b337c938a2953e5675f9dc18c99f05f4c85d0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


# --- Unit Tests -
enable_testing()
file(GLOB_RECURSE UNIT_TEST_FILES CONFIGURE_DEPENDS "src/*.unit.test.cpp")

add_executable(concorde_test ${UNIT_TEST_FILES})
target_link_libraries(concorde_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(concorde_test)