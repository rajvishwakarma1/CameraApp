cmake_minimum_required(VERSION 3.16)

project(CameraApp CXX)

# C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt's automatic features for UI files and signals/slots
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Dependencies
find_package(Qt6 REQUIRED COMPONENTS Widgets)

find_package(OpenCV REQUIRED)

# Define Executable
qt_add_executable(CameraApp
    main/main.cpp
    main/MainWindow.h
    main/MainWindow.cpp
    main/MainWindow.ui
)

# Link Libraries
target_link_libraries(CameraApp PRIVATE
    Qt6::Widgets
    ${OpenCV_LIBS}
)

install(TARGETS CameraApp
    RUNTIME DESTINATION bin
)

if(WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${Qt6_DIR}/bin")

    if(WINDEPLOYQT_EXECUTABLE)
        add_custom_command(
            TARGET CameraApp POST_BUILD
            COMMAND ${WINDEPLOYQT_EXECUTABLE}
            ARGS --dir "$<TARGET_FILE_DIR:CameraApp>" "$<TARGET_FILE:CameraApp>"
            COMMENT "Running windeployqt to automatically deploy Qt DLLs"
        )
    endif()
endif()