#include<iostream>
#include<glad/glad.h>

#include<GLFW/glfw3.h>
 
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
 
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
 
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Tutorial", NULL, NULL);
    if (window == NULL) {
        std::cout << "윈도우를 여는데 실패했다.\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD를 초기화하는데 실패했다.\n";
        return -1;
    }
    
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    glfwTerminate();
    return 0;
}

