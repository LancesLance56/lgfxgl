#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "gfx.h"

#include "GLFW/glfw3.h"

class Camera {
public:
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 direction;

    glm::mat4 mvp;
    glm::mat4 m_lookAt;
    glm::mat4 m_projection;
    glm::mat4 m_model;

    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 globalUp;
    glm::vec3 cameraFront;

    float yaw = -90;
    float pitch = 0;

    bool isFirstFrame = true;
    bool isSecondFrame = false;

    float yVelocity = 0.0f;
    float jumpVelocity = 4.0f;
    float gravity = 100.0f;

    // makes lookAt matrix

    Camera() = default;

    Camera(
      glm::vec3 position,
      glm::vec3 target,
      glm::vec3 globalUp,
      float aspect_ratio,
      float FOV = 45.0f,
      float near = 0.1f,
      float far = 100.f
    );

    void change_rotation(GLFWwindow* window, float xpos, float ypos, float mouseSensitivity);
    void moveCamera(glm::vec3 move_vector);
    void updateCamera();

};

#endif
