cmake_minimum_required (VERSION 3.0)

project("resmgr.sample")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../resmgr.common/cmake/Modules")

set(RESMGR_COMMON_PUBLIC_DIR "${CMAKE_HOME_DIRECTORY}/../resmgr.common/public/src")
if (NOT IS_DIRECTORY ${RESMGR_COMMON_PUBLIC_DIR})
	message(FATAL_ERROR "resmgr.common public directory does not exist: ${RESMGR_IMPL_DIR}")
endif()

find_package(ResCommon REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
