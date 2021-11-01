cmake_minimum_required(VERSION 3.10)

project(C3CPP VERSION 0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O3 -std=c++11 -foptimize-sibling-calls -Wno-unknown-warning-option")

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
include_directories(${BLAS_INCLUDE_DIR}, ${LAPACK_INCLUDE_DIR})
set(blas_lapack ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})

# Set c3 library
set(C3_LIB_PATH "" CACHE FILEPATH "Path to Compressed Continuous Computation (C3) library")
find_library(c3lib c3 PATHS ${C3_LIB_PATH})
if(NOT c3lib)
  message(FATAL_ERROR "c3 library not found in ${C3_LIB_PATH}")
endif()

include_directories(c3cpp)

add_subdirectory(c3cpp)
add_subdirectory(examples)
