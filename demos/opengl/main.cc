#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unistd.h>
#include "et.hpp"

GLFWwindow* window;

void errorCallback(int error, const char* msg)
{
    std::cout << error << " " << msg << '\n';
}

bool createWindow(int width, int height)
{
    glfwSetErrorCallback(errorCallback);
    
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    
    window = glfwCreateWindow(width, height, "Opengl Demo", nullptr, nullptr);
    if(!window) {
        glfwTerminate();
        return false;
    }
    
    glfwMakeContextCurrent(window);
    if(glewInit() != GLEW_OK) {
    std::cout << glGetError();
        std::cout << "Failed to initialize glew\n";
        glfwTerminate();
        return false;
    }
    
    // Viewport and projection
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 1.0, 425.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_FLAT); // GL_FLAT or GL_SMOOTH
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    return true;
}

void destroyWindow()
{
    glfwDestroyWindow(window);
}

int main(int argc, char** argv)
{
    using namespace Et::Graph;
    using namespace Et::Math;
    
    int width = 640;
    int height = 480;
    
    if(!createWindow(width, height)) return -1;
    
    OpenglRenderer renderer(width, height);
    Scene scene;
    
    Obj& camera = scene.createObj();
    camera.addComponent<Transform>(0.0f, 0.0f, 0.0f);
    // aspectRatio, fieldOfView, focalLength, aperture
    camera.addComponent<Camera>(Camera::AspectRatio(16.0f, 9.0f), 60.0f,  10.0f, 0.18f);
    
    Obj& box = scene.createObj();
    camera.addComponent<Transform>(0.0f, 0.0f, -3.0f);
    box.addComponent<SdfAaBox>(1.0f, 1.0f ,1.0f);
    
    while(true) {
        scene.update();
        renderer.render(scene, &camera);
        glfwSwapBuffers(window);
        usleep(16000);
    }
    
    destroyWindow();
    return 0;
}
