add_library(rescmn STATIC
            ${CMAKE_CURRENT_SOURCE_DIR}/impl/CQnxResMngImpl.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/impl/CUnknownResMngImpl.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/impl/callback/CQnxCallback.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/impl/data/CQnxResData.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/factory/CResourceMngFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/parser/CommandLine.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/parser/CProgramArgument.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/CResourceManagerImpl.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/CResourceManager.cpp)

target_include_directories(rescmn PUBLIC 
                           ${CMAKE_CURRENT_SOURCE_DIR} 
                           ${CMAKE_CURRENT_SOURCE_DIR}/impl
                           ${CMAKE_CURRENT_SOURCE_DIR}/factory
                           ${CMAKE_CURRENT_SOURCE_DIR}/impl/data)

install(TARGETS rescmn 
        EXPORT ResCommon
        ARCHIVE DESTINATION ${OUTPUT_ARCH}/lib)

install(FILES  
        CResourceManager.hpp
        CResourceManagerImpl.hpp
        DESTINATION ${CMAKE_HOME_DIRECTORY}/public/src)

add_subdirectory(devctl)
add_subdirectory(factory)
add_subdirectory(impl)
add_subdirectory(parser)
