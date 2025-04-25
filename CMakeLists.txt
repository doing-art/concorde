cmake_minimum_required(VERSION 3.27)
project(concorde)


# Set cmake variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Collect source files (excluding tests)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cc src/*.h)
set(MAIN_FILE "")
foreach(file ${SRC_FILES})
    if(file MATCHES "_test.cc$")
        list(REMOVE_ITEM SRC_FILES ${file})
    endif()
    if(file MATCHES "concorde\\.cc$")
        set(MAIN_FILE ${file})
        list(REMOVE_ITEM SRC_FILES ${file})
    endif()
endforeach()

add_executable(concorde ${SRC_FILES} ${MAIN_FILE})


# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


# Unit Tests
enable_testing()
file(GLOB_RECURSE UNIT_TEST_FILES CONFIGURE_DEPENDS "src/*_test.cc")

add_executable(concorde_test ${UNIT_TEST_FILES} ${SRC_FILES})
target_link_libraries(
    concorde_test   
    GTest::gtest
    GTest::gmock
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(concorde_test)


# Configure Clang Format
add_custom_target(
    clang-format
    COMMAND clang-format -i -style=file ${ALL_SRC_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-format on source files"
)


# Configure Clang Tidy
if(ENABLE_CLANG_TIDY)
    set_target_properties(concorde PROPERTIES CXX_CLANG_TIDY "clang-tidy")
    set_target_properties(concorde_test PROPERTIES CXX_CLANG_TIDY "clang-tidy")
endif()

add_custom_target(
    clang-tidy
    COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} -header-filter='src/.*' ${ALL_SRC_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
