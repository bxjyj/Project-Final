cmake_minimum_required(VERSION 3.28)
project(UFO)

set(CMAKE_CXX_STANDARD 17)

add_executable(UFO main.cpp Button.h
        HashMap.cpp UFO.h Map.h
        entryWindow.h
        resultsWindow.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

target_link_libraries(UFO sfml-system sfml-window sfml-graphics sfml-audio)
include_directories(c:/SFML/include/SFML)