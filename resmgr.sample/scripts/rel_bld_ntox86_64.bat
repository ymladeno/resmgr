@echo off
call ..\..\..\..\qnx700_2\qnx700_2\qnxsdp-env.bat

cd ..
mkdir build 2> null
rm null

cd build
rm -rf *
cmake -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=..\cmake\toolchains\win64_ntox86_64.cmake ..
pause