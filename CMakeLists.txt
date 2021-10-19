cmake_minimum_required(VERSION 3.20)
project(qt5_click_shapes)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(qt5_click_shapes main.cpp ClickShapeWidget.cpp ClickShapeWidget.h MainWindow.cpp MainWindow.h)
target_link_libraries(qt5_click_shapes
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

