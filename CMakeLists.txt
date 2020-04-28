cmake_minimum_required(VERSION 3.16)
project(facial_recognition)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/usr/local/Qt-5.14.2")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(OpenCV REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})


add_executable(facial_recognition main.cpp MainWindow.cpp MainWindow.h CameraWidget.cpp CameraWidget.h CentralWidget.cpp CentralWidget.h FacialRecognitionThread.cpp FacialRecognitionThread.h CascadeDetectorAdapter.cpp CascadeDetectorAdapter.h FacialRecognitionApplication.cpp FacialRecognitionApplication.h)

target_link_libraries(facial_recognition ${OpenCV_LIBS})
target_link_libraries(facial_recognition Qt5::Widgets)

