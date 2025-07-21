#include "game.h"
#include "gfx.h"
#include "handle_input.h"
#include "lightpos.h"
#include "testgui.h"
#include "lightpos.h"

int main() {
    Game::init();
    Game::calculate_delta_time();
    TestGUI::init(*Game::window); // DO NOT CHANGE THE ORDER

    while (!glfwWindowShouldClose(Game::window->window)) {
        if (shouldRenderGui)
            TestGUI::initializeFrame();

        glClearColor(SKY_BLUE.red, SKY_BLUE.green, SKY_BLUE.blue, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, polygon_modes[Game::window->current_polygon_mode_index]);
        glPointSize(4.0f);
        Game::render_loop();
        if (shouldRenderGui)
            TestGUI::renderGUI();

        glfwSwapBuffers(Game::window->window);
        glfwPollEvents();
        global_lights_last_frame = global_lights;
    }
}
