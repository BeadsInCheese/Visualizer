@echo off
if not exist build (
    mkdir build
)
cd build
cmake ..
cmake --build .
cd ..
xcopy /i "./Shaders" "./build/bin/Debug/Shaders"
xcopy /i "./Shaders" "./build/bin/Release/Shaders"
echo "build completed"
pause