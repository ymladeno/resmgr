@echo off
call C:\rtc_depot\workspace\Dijkstra\dk.os.qnx700\qnxsdp-env.bat

cd ..
mkdir build 2> null
rm null

cd build
rm -rf *

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=..\cmake\toolchains\win64_ntox86_64.cmake ..
pause
