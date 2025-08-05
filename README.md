# QT Webcam + Player

A professional, feature-rich webcam viewer and player application built with C++ and the Qt framework, developed as an assignment for VIR Innovations. The application provides a live camera feed, buffered playback controls, and a modern, minimal user interface.

## Demo

*(A screenshot of the final application UI would go here)*

A live demo of the application can be viewed on YouTube.
*(Note: You will need to upload your video to YouTube and replace `YOUTUBE_ID_HERE` with your video's ID)*

[![YouTube Demo](https://img.youtube.com/vi/Xmc5whRvbkQ/0.jpg)](https://www.youtube.com/watch?v=Xmc5whRvbkQ)

## Features

This application includes a wide range of features to meet and exceed the project requirements:

* **Live Camera Feed:** Displays a real-time video stream from the default system camera in a resizable window.
* **Buffered Playback:** The application continuously stores the last ~10 seconds of the live feed in a memory buffer.
* **Advanced Playback Controls**:
    * **Live Stream:** Start the live camera feed or return to it from playback mode.
    * **Pause:** A dual-function button to pause the live feed (entering playback mode) or pause the buffered playback itself.
    * **Resume:** A dedicated button to resume playback of the buffered video.
    * **Forward & Rewind:** Skip forward or backward through the buffered video by a set number of frames.
* **Interactive Timeline:** A slider allows for precise seeking within the buffered video history when paused.
* **Camera Configuration:**
    * Change the camera's resolution on-the-fly from a dropdown menu with common options (e.g., 640x480, 1280x720, 1920x1080).
    * The UI displays the current active resolution.
* **Professional User Interface:**
    * A clean, minimal, and professional dark theme inspired by modern development tools.
    * Clear iconography and text labels on all buttons for maximum usability.
    * Helpful tooltips to explain the function of each control.
* **Robust Error Handling:** The application gracefully handles potential runtime errors, such as the inability to access the camera or failure to set a resolution, and displays informative messages in the status bar without crashing.
* **Automated Dependency Deployment:** The build system is configured to automatically copy all required Qt and OpenCV DLLs next to the executable, making the application portable and easy to run without manual setup.

## Tech Stack

* **Language:** C++ (using the C++17 standard)
* **UI Framework:** Qt 6
* **Computer Vision:** OpenCV 4
* **Build System:** CMake
* **Version Control:** Git / GitHub

## Prerequisites (Windows 11)

To build and run this project, you will need the following software installed:

* **Visual Studio 2022:** With the "Desktop development with C++" workload.
* **Git for Windows**
* **CMake**
* **Qt 6 (MSVC Version):** Installed via the Qt Online Installer.
* **vcpkg:** With OpenCV installed via the command: `vcpkg install opencv4:x64-windows`.

## How to Build and Run

1.  **Clone the Repository**
    ```bash
    git clone <your-repo-url>
    cd <repo-name>
    ```

2.  **Configure with CMake**
    Open PowerShell and run the following command from the project's root directory. **Remember to replace the placeholder paths** with the actual paths to your `vcpkg` and `Qt` installations.

    ```powershell
    cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_PREFIX_PATH=C:\Qt\6.9.1\msvc2022_64
    ```

3.  **Compile the Project**
    This command will compile the source code and automatically run the deployment scripts to copy all necessary DLLs into the build folder.
    ```powershell
    cmake --build build
    ```

4.  **Run the Application**
    Navigate to the `build/Debug` directory and run the executable directly. **No need to set the PATH variable.**
    ```powershell
    .\build\Debug\CameraApp.exe
    ```

## Future Scope

While the current version fulfills all requirements, the following features could be added in the future:

* **Save/Record Video to File:** The feature we discussed but decided to leave for later. This would involve using OpenCV's `VideoWriter` class, likely in a separate thread to prevent UI lag.
* **Multiple Camera Support:** Add a feature to detect all connected cameras and allow the user to switch between them.
* **Real-time OpenCV Filters:** Implement a menu to apply real-time video effects, such as Grayscale, Edge Detection (Canny), or Blurring.
* **Saving Snapshots:** Add a button to capture the current frame and save it as a JPEG or PNG image.

## Author

* **Raj Vishwakarma**

### Acknowledgments
* An assignment for **VIR Innovations**.
