
#include "camera.h"

gfx::Camera::Camera(glm::vec3 position, glm::vec3 upVec) : cameraPosition(position), worldUp(upVec) {
    UpdateCameraVectors();
}

glm::mat4 gfx::Camera::GetViewMatrix() {
    return glm::lookAt(cameraPosition, cameraPosition + front, up);
}

void gfx::Camera::ProcessKeyboardMovement(gfx::CameraMovement direction, float deltaTime) {

    float velocity = movementSpeed * deltaTime;

    switch(direction){
        case CameraMovement::Forward:
            cameraPosition += front * velocity;
            break;
        case CameraMovement::Backward:
            cameraPosition -= front * velocity;
            break;
        case CameraMovement::Left:
            cameraPosition -= right * velocity;
            break;
        case CameraMovement::Right:
            cameraPosition += right * velocity;
            break;
    }
}

void gfx::Camera::ProcessMouseMovement(float xOffset, float yOffset) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw   += xOffset;
    pitch += yOffset;

    if(pitch > 89.0f){
        pitch = 89.0f;
    }

    if(pitch < -89.0f){
        pitch = -89.0f;
    }

    UpdateCameraVectors();
}

void gfx::Camera::UpdateCameraVectors() {
    front = glm::normalize(glm::vec3{cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                                     sin(glm::radians(pitch)),
                                     sin(glm::radians(yaw)) * cos(glm::radians(pitch))});

    //re-calculate right and up vectors
    right = glm::normalize(glm::cross(front, worldUp));
    up    = glm::normalize(glm::cross(right, front));
}

