project(readOutputFile C)

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

###############################################################################
# Set build features
set(CMAKE_BUILD_TYPE Debug)

#include(FindOpenACC)

set(STATIC_LINK ON)

###############################################################################
# Generate "config.h" from "cmake/config.h.cmake"
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/config.h)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-DHAVE_CONFIG_H)
set(CONFIG_HEADER ${CMAKE_CURRENT_BINARY_DIR}/config.h)

###############################################################################
# Subdirectories
add_subdirectory(src)
add_subdirectory(/home/kito/Dev/Sources/ACSEL/matrice_grad/src/tools Debug)
