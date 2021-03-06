cmake_minimum_required(VERSION 2.8.7)

project(orderbook CXX)

set(BASE_CXX_FLAGS "-m64 -fmessage-length=0 -std=c++11 -fPIC -fno-builtin -msse -msse4.1 -msse2 -msse4.2 -fdiagnostics-color=auto")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(PROJECT_TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(PROJECT_EXT_LIB_DIR ${CMAKE_SOURCE_DIR}/ext)


include_directories(SYSTEM "/usr/include")
include_directories(${CMAKE_SOURCE_DIR}/include)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${PROJECT_EXT_LIB_DIR}/googletest/googletest-src
                 ${PROJECT_EXT_LIB_DIR}/googletest/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.


add_subdirectory(src)
add_subdirectory(test)