cmake_minimum_required(VERSION 3.16)
project(MyGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add SFML library path
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/SFML")
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

add_subdirectory(src)
