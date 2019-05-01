cmake_minimum_required (VERSION 3.0)
project("resmgr.lib.srv")

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message(STATUS, "Debug configuration!")
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/dbg" CACHE FILEPATH "" FORCE)
else()
    message(STATUS, "Release configuration")
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/rel" CACHE FILEPATH "" FORCE)
endif()

set (RESMGR_COMMON_PUBLIC_DIR "${CMAKE_HOME_DIRECTORY}/../resmgr.common/public/src")
if (NOT IS_DIRECTORY ${RESMGR_COMMON_PUBLIC_DIR})
	message(FATAL_ERROR "Directory does not exist: ${RESMGR_COMMON_PUBLIC_DIR}")
endif()

add_subdirectory(src)
add_subdirectory(test)
