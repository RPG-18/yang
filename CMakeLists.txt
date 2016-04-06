cmake_minimum_required(VERSION 3.3)
project(yang)

option(TEST_ENABLE "enable tests" OFF)

# -Weffc++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Qml)
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5WebEngineWidgets)

add_definitions(
        ${Qt5Qml_DEFINITIONS}
        ${Qt5Core_DEFINITIONS}
        ${Qt5Widgets_DEFINITIONS}
        ${Qt5WebEngineWidgets_DEFINITIONS}
)
include_directories(
        ${Qt5Qml_INCLUDE_DIRS}
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5WebEngineWidgets_INCLUDE_DIRS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
include_directories(3rdparty/gumbo-parser/src
        src
        src/parsers)
add_subdirectory(3rdparty/gumbo-parser/src)

add_subdirectory(src)
if(TEST_ENABLE)
    enable_testing()
    add_subdirectory(3rdparty/gtest)
    include_directories(src
            3rdparty/gtest/include)
    add_subdirectory(test)
endif(TEST_ENABLE)

