cmake_minimum_required (VERSION 3.8)
project (QT )
find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_executable(QT main.pro main.cpp "main.h" "BMP.h" images.qrc "Histogram.h" "scena.h" "scena.cpp" "view.h" "view.cpp")
set_target_properties(QT PROPERTIES AUTOMOC TRUE)
set_target_properties(QT PROPERTIES AUTORCC TRUE)
set(CMAKE_AUTORCC ON)
target_link_libraries(QT
        Qt5::Widgets
        Qt5::Gui
        Qt5::QWindowsIntegrationPlugin)
