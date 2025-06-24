#!/bin/bash

echo "Building Library Management System - Qt GUI Version"
echo "=================================================="

# Check if Qt is installed
if ! command -v qmake &> /dev/null; then
    echo "Error: qmake not found. Please install Qt and add it to your PATH."
    echo "You can download Qt from: https://www.qt.io/download"
    echo "Or install via package manager:"
    echo "  Ubuntu/Debian: sudo apt install qt5-default qtcreator"
    echo "  macOS: brew install qt"
    exit 1
fi

# Check if CMake is installed
if command -v cmake &> /dev/null; then
    echo "Using CMake build system..."
    
    # Create build directory
    mkdir -p build
    cd build
    
    echo "Configuring with CMake..."
    cmake ..
    
    if [ $? -eq 0 ]; then
        echo "Building with CMake..."
        cmake --build .
        
        if [ $? -eq 0 ]; then
            echo "Build completed successfully!"
            echo "Executable location: bin/LibrarySystem"
            cd ..
            exit 0
        else
            echo "CMake build failed. Falling back to qmake..."
            cd ..
        fi
    else
        echo "CMake configuration failed. Falling back to qmake..."
        cd ..
    fi
else
    echo "CMake not found. Using qmake instead."
fi

# Fallback to qmake
echo "Using qmake build system..."
echo "Generating Makefile..."
qmake LibrarySystem.pro

if [ $? -ne 0 ]; then
    echo "Error: qmake failed to generate Makefile."
    exit 1
fi

echo "Building with make..."
make

if [ $? -ne 0 ]; then
    echo "Error: Build failed."
    exit 1
fi

echo "Build completed successfully!"
echo "Executable location: LibrarySystem"

echo ""
echo "To run the application:"
echo "- If using CMake: ./build/bin/LibrarySystem"
echo "- If using qmake: ./LibrarySystem"
echo "" 