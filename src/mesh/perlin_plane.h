#ifndef PERLIN_PLANE_H
#define PERLIN_PLANE_H

#include <vector>
#include <glm/glm.hpp>

#include "../mesh/mesh.h"
#include "imgui/animation_curve.h"
#include "material.h"
#include "math/perlin.h"
#include "shader.h"

class Camera;

class PerlinPlane {
public:
    PerlinPlane() = default;
    PerlinPlane(const std::shared_ptr<Shader>& shader,
                const PerlinPlaneSettings &settings,
                const std::vector<float> &LUT,
                const glm::vec3 &position = glm::vec3(0.0f));

    void draw(const glm::mat4 &vp, const Camera &camera) const;

private:
    Mesh<MeshType::COLOR_TEXTURE_NORMALS> mesh;
    std::vector<GLuint> terrainTexturesIDs;
    std::vector<float> LUT;
    glm::vec3 position = glm::vec3(0.0f);
};

#endif // PERLIN_PLANE_H
