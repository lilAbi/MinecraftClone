#include "application.h"

void core::Application::Init() {
    //set global event system
    core::Events::gEventSystem = &eventSystem;

    //create world
    world = new game::World(&camera);

    //initialize the ui

    //initialize the renderer

    //initialize the player
}


void core::Application::Run() {

    auto* glfwWindow = window.glfwWindow;

    while(!glfwWindowShouldClose(glfwWindow)){
        //process Input
        ProcessInput(glfwWindow);

        //if game state is in playing mode
        world->Update();

        //render
        Render();

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

}

void core::Application::ProcessInput(GLFWwindow* glfwWindow) {
    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(glfwWindow, true);
    }
}

void core::Application::Render() {
    renderer.Draw();
}

void core::Application::OnEvent(core::Events::Event event) {

}

void core::Application::PollEvents() {

}

