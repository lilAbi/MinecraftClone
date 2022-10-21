
#ifndef GAMEENGINEV2_CAMERA_H
#define GAMEENGINEV2_CAMERA_H
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace gfx{

    enum class CameraMovement{
        Forward = 0,
        Backward,
        Left,
        Right,
    };

    class Camera {
    public:
        explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 upVec = glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 GetViewMatrix();

        void ProcessKeyboardMovement(CameraMovement direction, float deltaTime);

        void ProcessMouseMovement(float xOffset, float yOffset);

    private:

        void UpdateCameraVectors();

    private:
        glm::vec3 cameraPosition;
        glm::vec3 worldUp;
        glm::vec3 front{0.0f, 0.0f, -1.0f};
        glm::vec3 up{0.0f, 0.0f, 0.0f};
        glm::vec3 right{0.0f, 0.0f, 0.0f};
        float yaw{-90.0f};
        float pitch{0.0f};
        float movementSpeed{2.5f};
        float mouseSensitivity{0.1f};
        float zoom{45.0f};
    };

}


#endif //GAMEENGINEV2_CAMERA_H
