set(ARCH                     "aarch64")
set(QCC_ARCH                 "gcc_${ARCH}")
set(OUTPUT_ARCH              "arm_aarch64")
set(CMAKE_SYSTEM_NAME         QNX)
set(CMAKE_CXX_STANDARD        11)
set(CMAKE_C_COMPILER          qcc.exe)
set(CMAKE_C_FLAGS             "${CMAKE_C_FLAGS} -lang-c -O0")
set(CMAKE_CXX_COMPILER        q++.exe)
set(CMAKE_CXX_FLAGS           "${CMAKE_CXX_FLAGS} -lang-c++ -O0")
set(CMAKE_C_COMPILER_TARGET   "${QCC_ARCH}")
set(CMAKE_CXX_COMPILER_TARGET "${QCC_ARCH}")
set(CMAKE_AR                  "qcc.exe" CACHE STRING "")
set(CMAKE_C_ARCHIVE_CREATE    "<CMAKE_AR> -V${QCC_ARCH} -A <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_CREATE  "<CMAKE_AR> -V${QCC_ARCH} -A <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_RANLIB              "${ARCH}-ranlib.exe" CACHE FILEPATH "" FORCE)
