cmake_minimum_required (VERSION 3.0)

project("resmgr.calc")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../resmgr.common/cmake/Modules")

find_package(ResCommon REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
