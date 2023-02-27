cmake_minimum_required(VERSION 3.24)
project(OpenGl_Sandbox)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(/opt/homebrew/include/)

add_executable(${PROJECT_NAME} main.cpp Rectangle.cpp Rectangle.h)
target_link_libraries(${PROJECT_NAME} OpenGL::GL GLUT::GLUT)