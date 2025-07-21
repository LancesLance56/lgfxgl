#ifndef WINDOW_H
#define WINDOW_H

#define WIDTH 800
#define HEIGHT 600

#include "glad_include.h"
#include "camera.h"

const GLenum polygon_modes[3] = {GL_FILL, GL_LINE, GL_POINT};

class Window {
public:
    unsigned int current_polygon_mode_index = 0;
    GLFWwindow *window;
    Camera *camera;

    Window();

    void setCamera(Camera &camera);
};

#endif
