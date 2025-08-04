# Camera Feed Application

## [cite_start]Project Overview [cite: 2]
This is a Qt-based C++ application that displays a live camera feed using the OpenCV library. It allows users to control the feed and adjust camera settings like resolution. [cite_start]The project is built with CMake and version-controlled with Git. [cite: 3, 11]

## Features
* [cite_start]**Camera Display**: Shows a live feed from the default system camera. [cite: 13]
* [cite_start]**Playback Controls**: Includes buttons for Play, Pause, and Resume. [cite: 17, 18, 19, 20] (Note: Forward/Rewind are not applicable to a live stream).
* [cite_start]**Resolution Settings**: Allows users to select the camera resolution from a dropdown menu ($640\times480$, $1280\times720$, etc.). [cite: 24, 26]
* [cite_start]**Error Handling**: Notifies the user if the camera cannot be accessed. [cite: 36, 59]

## Prerequisites
You will need the following software installed:
* A C++17 compliant compiler (GCC, Clang, MSVC)
* CMake (3.16+)
* Git
* Qt Framework (Qt 6+)
* OpenCV Library (4.x)

## How to Build and Run

1.  **Clone the repository:**
    ```bash
    git clone <your-repo-url>
    cd CameraApp
    ```
2.  **Configure with CMake:**
    * **On Linux/macOS:**
        ```bash
        cmake -B build
        ```
    * **On Windows (using vcpkg):**
        *Replace `C:/path/to/vcpkg` with your actual path.*
        ```powershell
        cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
        ```
3.  **Compile the source code:**
    ```bash
    cmake --build build
    ```
4.  **Run the application:**
    * **On Linux/macOS:**
        ```bash
        ./build/CameraApp
        ```
    * **On Windows:**
        ```powershell
        ./build/Debug/CameraApp.exe
        ```