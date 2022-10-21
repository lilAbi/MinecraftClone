
#ifndef GAMEENGINEV2_WINDOW_H
#define GAMEENGINEV2_WINDOW_H
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace core{

    class Window {
    public:
        Window(int winWidth, int winHeight);
        ~Window();

    public:
        int width{1080};
        int height{720};
        GLFWwindow* glfwWindow{nullptr};
    };
}


#endif //GAMEENGINEV2_WINDOW_H
