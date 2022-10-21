
#include "window.h"

core::Window::Window(int winWidth, int winHeight) : width(winWidth), height(winHeight) {
    //initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //create window
    glfwWindow = glfwCreateWindow(width, height, "Minecraft Clone", nullptr, nullptr);

    //test if window is created
    if(!glfwWindow){
        std::cout << "Failed to initialize GLFW\n";
        glfwTerminate();
        return;
    }

    //set current glfw context to this window
    glfwMakeContextCurrent(glfwWindow);
    //tell glfw to show our mouse pointer
    //glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //get all opengl function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
}

core::Window::~Window() {
    glfwTerminate();
}
