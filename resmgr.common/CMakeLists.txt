cmake_minimum_required (VERSION 3.0)
project("resmgr.common")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message(STATUS, "Debug configuration!")
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/dbg" CACHE FILEPATH "" FORCE)
else()
    message(STATUS, "Release configuration")
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/rel" CACHE FILEPATH "" FORCE)
endif()

add_subdirectory(src)

