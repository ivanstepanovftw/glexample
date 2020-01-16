cmake_minimum_required(VERSION 3.15)
project(glexample_bundle)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
include(GNUInstallDirs)
#include(${CMAKE_SOURCE_DIR}/cmake/properties.cmake)
#include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)
#include(${CMAKE_SOURCE_DIR}/cmake/dependencies.cmake)
##include(${CMAKE_SOURCE_DIR}/cmake/PVS-Studio.cmake) # TODO[critical]: CMakeLists.txt: what if PVS-Studio.lic not exists?
#include(${CMAKE_SOURCE_DIR}/cmake/versioning.cmake)

add_subdirectory(glexample)
add_subdirectory(mypony)
