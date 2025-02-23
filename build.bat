@echo off
if not exist build (
    mkdir build
)
cd build
cmake ..
cmake --build .
cd ..
echo "build completed"
pause