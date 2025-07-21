#include "game.h"

#include "gfx/lightpos.h"
#include "gfx/material.h"
#include "handle_input.h"
#include "imgui/animation_curve.h"
#include "math/perlin.h"

#include <GLFW/glfw3.h>
#include <array>
#include <iostream>
#include <string>

#include "testgui.h"

// Static member definitions
std::unique_ptr<Window> Game::window = nullptr;
std::unique_ptr<PerlinPlane> Game::perlinPlane = nullptr;
std::shared_ptr<Shader> Game::perlinPlaneShader;
Camera Game::camera;
Renderer Game::renderer;
std::vector<Cube> Game::cubes;
std::vector<float> Game::heightMapLUT;

double Game::deltaTime = 0.0;
double Game::oldTimeLog = 0.0;
int Game::seed = 0;
unsigned int Game::meshResolution = 3;
float Game::sensitivity = 0.05f;
unsigned int Game::sizeOfMesh = 10;
float Game::scale = 3.0f;
float Game::heightMultiplier = 8.0f;
int Game::octaves = 5;
float Game::persistence = 0.5f;
float Game::lacunarity = 2.0f;
int Game::heightMapLUTResolution = 10;
glm::vec2 Game::perlinOffset = glm::vec2(0.0f, 0.0f);
glm::vec3 Game::perlinPosition = glm::vec3(0.0f);
glm::vec3 currentPosition = glm::vec3(0.0f);

// Helper to print OpenGL errors
void checkGLError(const std::string &stage) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "[OpenGL ERROR] (" << err << ") during " << stage << "\n";
    }
}

PerlinPlaneSettings getCurrentPerlinPlaneSettings() {
    return {Game::sizeOfMesh, Game::meshResolution,   Game::perlinOffset.x, Game::perlinOffset.y, Game::scale,
            Game::seed,       Game::heightMultiplier, Game::octaves,        Game::persistence,    Game::lacunarity};
}

bool has_perlin_settings_changed() {
    static PerlinPlaneSettings previousSettings;

    if (const auto current = getCurrentPerlinPlaneSettings();
        current != previousSettings || currentPosition != Game::perlinPosition) {
        previousSettings = current;
        std::cout << "[INFO] Perlin settings changed — rebuilding mesh.\n";
        return true;
    }
    return false;
}

void Game::calculate_delta_time() {
    deltaTime = glfwGetTime() - oldTimeLog;
    oldTimeLog = glfwGetTime();
}

void rebuild_perlin_mesh() {
    Game::perlinPlane = std::make_unique<PerlinPlane>(
            Game::perlinPlaneShader, getCurrentPerlinPlaneSettings(), Game::heightMapLUT, Game::perlinPosition);
}

void Game::render_loop() {
    calculate_delta_time();
    handleInput(window->window);

    for (const auto &[position, color]: global_lights) {
        cubes.emplace_back(position, glm::vec3(0.0f), 1, color);
    }

    if (has_perlin_settings_changed()) {
        rebuild_perlin_mesh();
    }

    camera.moveCamera(handleMovement(window->window, camera.cameraFront, camera.globalUp, deltaTime));
    camera.updateCamera();

    if (perlinPlane)
        perlinPlane->draw(camera.mvp, camera);

    for (const auto &cube: cubes) {
        cube.draw(camera.mvp, camera);
    }

    if (TestGUI::myCurve != TestGUI::previousCurve && !TestGUI::editor.isAPointSelected) {
        heightMapLUT = BezierEditor::computeHeightRemapLUT(TestGUI::myCurve, heightMapLUTResolution);
        std::cout << heightMapLUT[4] << std::endl;
        rebuild_perlin_mesh();
    }

    cubes.clear();
    currentPosition = Game::perlinPosition;
    TestGUI::previousCurve = TestGUI::myCurve;
}

void Game::init() {
    calculate_delta_time();

    window = std::make_unique<Window>();
    camera =
            Camera(glm::vec3(-5.0f, 10.0f, 4.5f),
                   glm::vec3(static_cast<float>(sizeOfMesh), 0.0f, static_cast<float>(sizeOfMesh)),
                   glm::vec3(0.0f, 1.0f, 0.0f), static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT);
    perlinPlaneShader =
            std::make_shared<Shader>("./src/shaders/textured_terrain.vert", "./src/shaders/textured_terrain.frag");

    window->setCamera(camera);
}
