# Cmake build for piESocket controll program tests

cmake_minimum_required(VERSION 3.13.0)

project(eSocket_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

find_package(GTest REQUIRED)

find_library(RT_LIB_EX NAMES rt)
if (NOT RT_LIB_EX)
	message(FATAL_ERROR "RT library not found")
endif()

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "Setting build type to 'Release'")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Default build type: Release" FORCE)
endif()

# Compiler options
add_compile_options(-Wall)

add_executable(${PROJECT_NAME} "")
# source files
include(${PROJECT_SOURCE_DIR}/sourcelist.cmake)

target_link_libraries(${PROJECT_NAME} gtest Threads::Threads rt)
target_include_directories(${PROJECT_NAME} PRIVATE
	"../src/program"
	"../src/utils"
)
