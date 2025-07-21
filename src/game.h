#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "camera.h"
#include "math/perlin_noise_map.h"
#include "mesh/cube.h"
#include "mesh/perlin_plane.h"
#include "renderer.h"
#include "shader.h"
#include "window.h"

class Game {
public:
    // Global game objects
    static std::unique_ptr<Window> window;
    static std::unique_ptr<PerlinPlane> perlinPlane;
    static std::shared_ptr<Shader> perlinPlaneShader;
    static Camera camera;
    static Renderer renderer;
    static std::vector<Cube> cubes;
    static std::vector<float> heightMapLUT;

    // Runtime globals
    static PerlinPlaneSettings perlinSettings;
    static glm::vec2 perlinOffset;
    static glm::vec3 perlinPosition;
    static double deltaTime;
    static double oldTimeLog;
    static int seed;
    static unsigned int meshResolution;
    static float sensitivity;
    static unsigned int sizeOfMesh;
    static float scale;
    static float heightMultiplier;
    static int octaves;
    static float persistence;
    static float lacunarity;
    static int heightMapLUTResolution;

    static void calculate_delta_time();
    static void render_loop();
    static void init();
};

#endif
