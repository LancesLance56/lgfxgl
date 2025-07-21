#include "camera.h"

Camera::Camera(
   const glm::vec3 position,
   const glm::vec3 target,
   const glm::vec3 globalUp,
   const float aspect_ratio,
   const float FOV /*= 45.0f*/,
   const float near /*= 0.1f*/,
   const float far /*= 100.f*/
) {

   this->position = position;
   this->target = target;
   this->globalUp = globalUp;

   // initialize vectors
   cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

   // m denotes mat4
   m_lookAt = glm::lookAt(position, target, globalUp); // camera
   m_projection = glm::perspective(glm::radians(FOV), aspect_ratio, near, far);
   m_model = glm::mat4(1.0f);

   mvp = m_model * m_lookAt * m_projection;
}

void Camera::change_rotation(GLFWwindow* window, const float xpos, const float ypos, float mouseSensitivity) {
    // to make sure that the delta mouse coords doesn't freak out and move the camera too much
    if (isFirstFrame) {
        isFirstFrame = false;
        isSecondFrame = true;
    } else if (isSecondFrame) {
        glfwSetCursorPos(window, static_cast<float>(SCREEN_WIDTH)/2, static_cast<float>(SCREEN_HEIGHT)/2);
        isSecondFrame = false;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT)) return;

    const float deltaMouseX = xpos - static_cast<float>(SCREEN_WIDTH)/2;
    const float deltaMouseY = static_cast<float>(SCREEN_HEIGHT)/2 - ypos;

    yaw += deltaMouseX * mouseSensitivity;
    pitch += deltaMouseY * mouseSensitivity;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = static_cast<float>(cos(glm::radians(yaw))) * cos(glm::radians(pitch));
    front.y = static_cast<float>(sin(glm::radians(pitch)));
    front.z = static_cast<float>(sin(glm::radians(yaw))) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

    glfwSetCursorPos(window, static_cast<float>(SCREEN_WIDTH)/2, static_cast<float>(SCREEN_HEIGHT)/2);
}

void Camera::moveCamera(const glm::vec3 move_vector) {
    if (move_vector != glm::vec3(0.0f, 0.0f, 0.0f)) {
        position -= move_vector;
        m_lookAt = glm::translate(m_lookAt, move_vector);
    }
}

void Camera::updateCamera() {
    m_lookAt = glm::lookAt(position, position + cameraFront, globalUp);

    mvp = m_projection * m_lookAt * m_model;
}