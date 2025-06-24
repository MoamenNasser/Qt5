# Library Management System - Qt GUI Version

This is a Qt-based GUI application for the Library Management System, converted from the original console-based C++ application.

## Features

### Book Management
- Add new books to the library
- Edit existing book details
- Remove books from the library
- Search for books by various criteria
- View all books in a table format

### Member Management
- Register new members
- Cancel member registrations
- Search for members
- View member information and fine balances

### Book Operations
- Checkout books to members
- Return books from members
- Renew book loans
- Reserve books
- Track due dates and overdue books

### Fine Management
- View member fine balances
- Process fine payments
- Automatic fine calculation for overdue books

### Notifications
- Real-time system notifications
- Overdue book alerts
- Transaction logging

## Prerequisites

### Required Software
1. **Qt Development Environment**
   - Qt 5.15+ or Qt 6.x
   - Qt Creator (recommended IDE)
   - Qt Designer (for UI editing)

2. **C++ Compiler**
   - GCC 7+ (Linux/macOS)
   - MSVC 2019+ (Windows)
   - Clang 10+ (macOS)

3. **Build System**
   - CMake 3.16+
   - qmake (alternative to CMake)

## Installation & Setup

### Option 1: Using Qt Creator (Recommended)

1. **Install Qt Creator**
   ```bash
   # Download from https://www.qt.io/download
   # Or use package manager:
   # Ubuntu/Debian: sudo apt install qtcreator
   # macOS: brew install qt-creator
   ```

2. **Open Project**
   - Launch Qt Creator
   - Open the `LibrarySystem.pro` file
   - Configure the project with your Qt installation

3. **Build and Run**
   - Click the "Build" button (hammer icon)
   - Click the "Run" button (play icon)

### Option 2: Using CMake

1. **Create Build Directory**
   ```bash
   mkdir build
   cd build
   ```

2. **Configure with CMake**
   ```bash
   cmake ..
   ```

3. **Build the Project**
   ```bash
   cmake --build .
   ```

4. **Run the Application**
   ```bash
   ./bin/LibrarySystem  # Linux/macOS
   bin\LibrarySystem.exe # Windows
   ```

### Option 3: Using qmake

1. **Generate Makefile**
   ```bash
   qmake LibrarySystem.pro
   ```

2. **Build the Project**
   ```bash
   make  # Linux/macOS
   nmake # Windows with MSVC
   ```

3. **Run the Application**
   ```bash
   ./LibrarySystem  # Linux/macOS
   LibrarySystem.exe # Windows
   ```

## Project Structure

```
LibrarySystem/
├── main.cpp                 # Qt application entry point
├── mainwindow.h             # Main window header
├── mainwindow.cpp           # Main window implementation
├── mainwindow.ui            # Qt Designer UI file
├── LibrarySystem.pro        # Qt project file
├── CMakeLists.txt           # CMake build file
├── inc/                     # Header files
│   ├── Book.h
│   ├── BookItem.h
│   ├── Member.h
│   ├── Librarian.h
│   ├── Library.h
│   ├── Transaction.h
│   ├── Observer.h
│   ├── NotificationService.h
│   └── Subject.h
├── src/                     # Source files
│   ├── Book.cpp
│   ├── BookItem.cpp
│   ├── Member.cpp
│   ├── Librarian.cpp
│   ├── Library.cpp
│   ├── Transaction.cpp
│   ├── Observer.cpp
│   ├── NotificationService.cpp
│   └── Subject.cpp
└── README_Qt.md            # This file
```

## Using Qt Designer

### Opening the UI File
1. Launch Qt Designer
2. Open `mainwindow.ui`
3. The UI will show the basic tab widget structure

### Customizing the Interface
1. **Adding Widgets**: Drag widgets from the widget box to the form
2. **Layout Management**: Use layout widgets to organize components
3. **Property Editor**: Modify widget properties in the property editor
4. **Signal/Slot Editor**: Connect signals and slots for event handling

### Key Qt Designer Features
- **Widget Box**: Contains all available Qt widgets
- **Object Inspector**: Shows widget hierarchy
- **Property Editor**: Modify widget properties
- **Signal/Slot Editor**: Connect events to functions
- **Action Editor**: Create menu actions

## GUI Features

### Tab-Based Interface
The application uses a tab widget with 5 main sections:

1. **Book Management Tab**
   - Form for adding/editing books
   - Table showing all books
   - Search and filter capabilities

2. **Member Management Tab**
   - Member registration form
   - Member list table
   - Membership management tools

3. **Book Operations Tab**
   - Checkout/return forms
   - Transaction history table
   - Renewal and reservation tools

4. **Fine Management Tab**
   - Fine payment interface
   - Fine balance display
   - Payment processing

5. **Notifications Tab**
   - System notification log
   - Real-time updates
   - Event history

### Real-Time Updates
- Tables automatically refresh when data changes
- Notifications appear in real-time
- Overdue book checking runs every minute

## Development Tips

### Adding New Features
1. **UI Changes**: Use Qt Designer to modify `mainwindow.ui`
2. **Logic Changes**: Modify `mainwindow.cpp` for new functionality
3. **Data Model**: Update the Library class for new data structures

### Debugging
1. **Qt Creator Debugger**: Use built-in debugger in Qt Creator
2. **Console Output**: Check console for debug messages
3. **Qt Debug Tools**: Use Qt's debugging utilities

### Styling
1. **QSS (Qt Style Sheets)**: Apply CSS-like styling
2. **Qt Designer**: Use the style sheet editor
3. **Theme Support**: Implement dark/light themes

## Troubleshooting

### Common Issues

1. **Qt Not Found**
   ```bash
   # Set Qt path environment variable
   export QT_DIR=/path/to/qt
   export PATH=$QT_DIR/bin:$PATH
   ```

2. **Build Errors**
   - Ensure all Qt modules are installed
   - Check C++ standard compatibility
   - Verify include paths

3. **Runtime Errors**
   - Check Qt library installation
   - Verify DLL dependencies (Windows)
   - Check file permissions

### Getting Help
- Qt Documentation: https://doc.qt.io/
- Qt Forum: https://forum.qt.io/
- Stack Overflow: Search for Qt-related questions

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is part of the Library Management System educational project.

## Acknowledgments

- Original console application by Moamen
- Qt Framework for GUI capabilities
- C++ Standard Library for data structures 