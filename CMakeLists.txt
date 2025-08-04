# Minimum CMake version required
cmake_minimum_required(VERSION 3.16)

# Project name and language
project(CameraApp CXX)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt's automatic features for UI files and signals/slots
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# --- Find Dependencies ---
# Find the Qt6 package, specifically the Widgets component [cite: 53]
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Find the OpenCV package [cite: 53]
find_package(OpenCV REQUIRED)

# --- Define Executable ---
# Add the executable target, linking the source files
qt_add_executable(CameraApp
    main/main.cpp
    main/MainWindow.h
    main/MainWindow.cpp
    main/MainWindow.ui
)

# --- Link Libraries ---
# Link the Qt and OpenCV libraries to your application
target_link_libraries(CameraApp PRIVATE
    Qt6::Widgets
    ${OpenCV_LIBS}
)

# --- Installation (Optional but good practice) ---
# Defines where the executable should be installed
install(TARGETS CameraApp
    RUNTIME DESTINATION bin
)