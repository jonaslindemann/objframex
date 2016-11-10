@echo off

set OSG_DIR="c:\\Users\\Jonas\\Development\\OpenSceneGraph-runtime"
set OSG_THIRD_PARTY_DIR="c:\\Users\\Jonas\\Development\\3rdParty"
set OCULUS_SDK_ROOT_DIR="c:\\Users\\Jonas\\Development\\OculusSDK"
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
cmake -DOSG_DIR=%OSG_DIR% -DOSG_THIRD_PARTY_DIR=%OSG_THIRD_PARTY_DIR% -DOCULUS_SDK_ROOT_DIR=%OCULUS_SDK_ROOT_DIR% ..
cd ..
