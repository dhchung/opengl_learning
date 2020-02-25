cmake_minimum_required(VERSION 3.0)
project(myopengl)
add_subdirectory(glad/)

set(CMAKE_CXX_COMPILER g++)
set(SOURCES src/learnopengl_hellotriangle_4.cpp glad/src/glad.c)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.2 REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw ${GLEW_LIBRARIES} glad ${CMAKE_DL_LIBS})