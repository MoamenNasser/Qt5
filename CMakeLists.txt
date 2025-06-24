cmake_minimum_required(VERSION 3.16)

project(LibrarySystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 or Qt5
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
if (NOT Qt6_FOUND)
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
endif()

# Set up Qt MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Include directories
include_directories(inc)

# Source files
set(SOURCES
    main.cpp
    mainwindow.cpp
    src/Book.cpp
    src/BookItem.cpp
    src/Member.cpp
    src/Librarian.cpp
    src/Library.cpp
    src/Transaction.cpp
    src/Observer.cpp
    src/NotificationService.cpp
    src/Subject.cpp
)

# Header files
set(HEADERS
    mainwindow.h
    inc/Book.h
    inc/BookItem.h
    inc/Member.h
    inc/Librarian.h
    inc/Library.h
    inc/Transaction.h
    inc/Observer.h
    inc/NotificationService.h
    inc/Subject.h
)

# UI files
set(UI_FILES
    mainwindow.ui
)

# Create executable
add_executable(LibrarySystem ${SOURCES} ${HEADERS} ${UI_FILES})

# Link Qt libraries
target_link_libraries(LibrarySystem Qt::Core Qt::Widgets)

# Set output directory
set_target_properties(LibrarySystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Platform-specific settings
if(WIN32)
    set_target_properties(LibrarySystem PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Install rules
install(TARGETS LibrarySystem
    RUNTIME DESTINATION bin
) 