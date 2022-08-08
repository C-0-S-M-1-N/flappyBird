cmake_minimum_required(VERSION 3.10.2)

project(bird)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-audio sfml-graphics sfml-window)
