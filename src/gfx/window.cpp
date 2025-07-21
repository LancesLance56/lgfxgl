#include "window.h"
#include <iostream>

#include "glad/glad.h"

void cursor_position_callback(GLFWwindow* window, double x, double y);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void changePolygonMode();

unsigned int* current_polygon_mode_index_ptr;
Camera *currentCamera;

Window::Window() {
    current_polygon_mode_index_ptr = &current_polygon_mode_index;

    if (!glfwInit()) {
        std::cerr << "[ERROR] Failed to initialize GLFW!\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "learnopengl", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "[ERROR] Failed to create a GLFW window!\n";
        glfwTerminate();
        return;
    }

    // Set the OpenGL context
    glfwMakeContextCurrent(window);

    // Load OpenGL functions with GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "[ERROR] Failed to initialize GLAD!\n";
        glfwDestroyWindow(window);
        window = nullptr;
        return;
    }

    // Input settings and callbacks
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    std::cout << "[INFO] Window and OpenGL initialized.\n";
}


void Window::setCamera(Camera &c) {
    this->camera = &c;
    currentCamera = this->camera;
};

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (currentCamera == nullptr) {
        std::cout << "Didn't connect a camera to the window" << std::endl;
        return;
    }

    currentCamera->change_rotation(window, xpos, ypos, 0.1f);
}


void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
   glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, true);
                break;
            case GLFW_KEY_M:
                changePolygonMode();
                break;
            default:
                break;
        }
    }
}

void changePolygonMode() {
   if ((*current_polygon_mode_index_ptr) == 2) {
      (*current_polygon_mode_index_ptr) = 0;
   } else {
      (*current_polygon_mode_index_ptr)++;
   }
}