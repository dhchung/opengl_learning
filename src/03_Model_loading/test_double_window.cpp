#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

int screenWidth = 1600;
int screenHeight = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float lastX = (float)screenWidth/2.0f;
float lastY = (float)screenHeight/2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main() {
    glfwInit(); //Initialize GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3); //OpenGL 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Use only core profiles of opengl
    //Setting up GLFW : https://www.glfw.org/docs/latest/window.html#window_hints

    //Making window
    GLFWwindow * window = glfwCreateWindow(screenWidth,screenHeight, "LearnOpenGL", NULL, NULL);

    if(window == NULL) {
        std::cout << "Failed to create GLFW wi3ndow" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window); //Tell GLFW to setup "window context" as primary context for current thread
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //GLAD : take care of the OpenGL function pointer : Need to initialize it before calling OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //glfwGetProcAddress : Get correct functions regarding to OS or compile environment
        std::cout<< "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    //Shaders
    Shader ourShader("shaders/model_loading/model_loading.vs", "shaders/model_loading/model_loading.fs");

    Model ourModel("assets/objects/nanosuit/nanosuit.obj");
    // Model ourModel("assets/objects/obj_test/airboat.obj");
    

    while(!glfwWindowShouldClose(window)) { //Check if there's any command to close the window to GLFW
        processInput(window);

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, screenWidth/2, screenHeight);
        ourShader.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth/2/(float)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f));
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        glViewport(screenWidth/2, 0, screenWidth/2, screenHeight);
        
        // ourShader.use();
        projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth/2/(float)screenHeight, 0.1f, 100.0f);
        view = camera.GetViewMatrix_right();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // glm::mat4 model = glm::mat4(1.0f);
        // model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        // model = glm::scale(model, glm::vec3(0.2f));
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        // camera.ProcessInput(-0.01,0.0,0.0,0.0,0.0,0.0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
    
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) { // Change viewport if the user change the size of the window
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.MovementSpeed = camera.FastSpeed;
    } else {
        camera.MovementSpeed = camera.OriginalSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos) {
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}
