@echo off
echo Building Library Management System - Qt GUI Version
echo ==================================================

REM Check if Qt is installed
where qmake >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: qmake not found. Please install Qt and add it to your PATH.
    echo You can download Qt from: https://www.qt.io/download
    pause
    exit /b 1
)

REM Check if CMake is installed
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo Warning: CMake not found. Using qmake instead.
    goto :qmake_build
)

echo Using CMake build system...
if not exist build mkdir build
cd build

echo Configuring with CMake...
cmake .. -G "Visual Studio 16 2019" -A x64
if %errorlevel% neq 0 (
    echo CMake configuration failed. Trying with default generator...
    cmake ..
)

if %errorlevel% neq 0 (
    echo CMake failed. Falling back to qmake...
    cd ..
    goto :qmake_build
)

echo Building with CMake...
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo CMake build failed. Falling back to qmake...
    cd ..
    goto :qmake_build
)

echo Build completed successfully!
echo Executable location: build\bin\Release\LibrarySystem.exe
cd ..
goto :end

:qmake_build
echo Using qmake build system...
echo Generating Makefile...
qmake LibrarySystem.pro
if %errorlevel% neq 0 (
    echo Error: qmake failed to generate Makefile.
    pause
    exit /b 1
)

echo Building with nmake...
nmake
if %errorlevel% neq 0 (
    echo Error: Build failed.
    pause
    exit /b 1
)

echo Build completed successfully!
echo Executable location: LibrarySystem.exe

:end
echo.
echo To run the application:
echo - If using CMake: build\bin\Release\LibrarySystem.exe
echo - If using qmake: LibrarySystem.exe
echo.
pause 