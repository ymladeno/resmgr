@echo off
call ..\..\..\qnx700_2\qnx700-env.bat

rem create new directory
mkdir build 2> null
rm null
cd build
rem cleanup in case directory is not new
rm -rf *

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=..\cmake\toolchains\win64_ntox86_64.cmake ..
