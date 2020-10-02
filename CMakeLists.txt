cmake_minimum_required(VERSION 3.17)
project(dot-rush)

set(CMAKE_CXX_STANDARD 20)

add_executable(dot-rush main.cpp src/dots.cpp src/dots.h src/brain.cpp src/brain.h src/population.cpp src/population.h src/obstacle.cpp src/obstacle.h)

find_package(SFML 2 REQUIRED graphics)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(dot-rush sfml-graphics)
endif()