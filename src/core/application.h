
#ifndef GAMEENGINEV2_APPLICATION_H
#define GAMEENGINEV2_APPLICATION_H
#include "world/world.h"
#include "graphics/renderer.h"
#include "graphics/camera.h"
#include "window.h"
#include "eventSystem.h"

namespace core{

    enum class ApplicationState{
        StartUpState = 0,
        MenuState,
        SettingState,
        WorldSelectionState,
        WorldCreationState,
        PlayingState,
        PausingState,
        UnknownState,
    };

    //game application class
    class Application {
    public:
        Application() = default;
        ~Application() = default;

        void Init();
        void Run();
        void ProcessInput(GLFWwindow* glfwWindow);
        void Render();

    private:
        void OnEvent(core::Events::Event event);
        void PollEvents();


    public:
        //world
        game::World* world;
        //user controllable camera
        gfx::Camera camera;
        //window object
        core::Window window{1920, 1080};
        //rendering system
        gfx::Renderer renderer;
        //system to process events
        core::Events::EventSystem eventSystem;
        //state of the application
        ApplicationState gameState = ApplicationState::StartUpState;
    };

}


#endif //GAMEENGINEV2_APPLICATION_H
