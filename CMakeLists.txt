cmake_minimum_required(VERSION 3.0)
project(myopengl)
add_subdirectory(glad/)

set(CMAKE_CXX_COMPILER g++)
set(SOURCES src/02_Lighting/01_Colors/color_3.cpp)
set(LIB_SOURCES glad/src/glad.c)
set(CLASS_SOURCES classes/shader.cpp classes/stb_image.cpp classes/camera.cpp classes/mesh.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.2 REQUIRED)

if (assimp_FOUND)
    set(ASSIMP_LIBRARY "assimp")
    add_library(${ASSIMP_LIBRARY} SHARED IMPORTED)
    set_target_properties(${ASSIMP_LIBRARY} PROPERTIES IMPORTED_LOCATION "${ASSIMP_LIBRARY_DIRS}/libassimp.so")
endif(assimp_FOUND)

add_executable(${PROJECT_NAME} 
               ${SOURCES} ${LIB_SOURCES} ${CLASS_SOURCES})

include_directories(${OPENGL_INCLUDE_DIRS} 
                    ${GLUT_INCLUDE_DIRS} 
                    ${GLM_INCLUDE_DIRS})

include_directories(classes/)
target_link_libraries(${PROJECT_NAME}
                      ${OPENGL_LIBRARIES} 
                      ${GLUT_LIBRARIES} 
                      glfw 
                      ${GLEW_LIBRARIES} 
                      ${GLM_LIBRARY_DIRS}
                      ${ASSIMP_LIBRARY}
                      glad ${CMAKE_DL_LIBS})