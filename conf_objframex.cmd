@echo off

rem OSG_ROOT="D:\Users\Jonas\Libraries\OpenSceneGraph-3.4.0\build"
rem set OSG_DIR="D:\Users\Jonas\Libraries\OpenSceneGraph-3.4.0\build"
rem OSG_SOURCE="D:\\Users\\Jonas\\Libraries\\OpenSceneGraph-3.4.0"
rem OSG_BIN_PATH = %OSG_ROOT%\bin
rem OSG_INCLUDE_PATH = %OSG_ROOT%\include
rem OSG_LIB_PATH = %OSG_ROOT%\lib
rem OSG_FILE_PATH=D:\Users\Jonas\Libraries\OpenSceneGraph-Data

if exist build (
    echo Removing old build
    rmdir /S /Q build
)

echo Create build dir
mkdir build

echo Configuring debug

cd build
cmake -DCMAKE_MODULE_PATH="%OSG_SOURCE%\\CMakeModules" ..
cd ..
