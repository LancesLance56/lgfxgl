#include "perlin_plane.h"
#include "../math/perlin_noise_map.h"

#include <iostream>
#include <numeric>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>

void bindTerrainTextures(GLuint shaderProgram, const std::vector<GLuint>& textureIDs, const std::string& uniformName) {
    glUseProgram(shaderProgram);

    for (size_t i = 0; i < textureIDs.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
        glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
    }

    GLint location = glGetUniformLocation(shaderProgram, uniformName.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform \"" << uniformName << "\" not found in shader.\n";
        return;
    }

    std::vector<GLint> units(textureIDs.size());
    std::iota(units.begin(), units.end(), 0);
    glUniform1iv(location, static_cast<GLsizei>(textureIDs.size()), units.data());
}

PerlinPlane::PerlinPlane(
        const std::shared_ptr<Shader>& shader,
        const PerlinPlaneSettings &settings,
        const std::vector<float> &LUT,
        const glm::vec3 &position)
    : mesh(Mesh<MeshType::COLOR_TEXTURE_NORMALS>()), position(position)
{
    // Generate mesh data once
    const auto perlinMeshSettings = PerlinMesh(PerlinPlaneSettings{
        settings.sizeOfMesh,
        settings.meshResolution,
        settings.x_offset,
        settings.z_offset,
        settings.scale,
        settings.seed,
        settings.heightMultiplier,
        settings.octaves,
        settings.persistence,
        settings.lacunarity});

    const unsigned int meshVertexCount = settings.sizeOfMesh * settings.meshResolution;
    const size_t vertexDataSize = meshVertexCount * meshVertexCount * 8;
    const size_t indexDataSize = (meshVertexCount - 1) * (meshVertexCount - 1) * 6;

    // Initialize the mesh member
    mesh = Mesh<MeshType::COLOR_TEXTURE_NORMALS>(
            shader,
            "", // texture path (unused here)
            perlinMeshSettings.indices, perlinMeshSettings.vertices,
            vertexDataSize, indexDataSize,
            glm::vec3(1.0f), glm::mat4(1.0f));

    const Shader &rendererShader = *mesh.renderer.shader;
    rendererShader.use();

    // Terrain definitions
    const std::vector<glm::vec3> terrainColors = {
            {0.0f, 0.1f, 0.4f},    // Deep water
            {0.0f, 0.3f, 0.7f},    // Shallow water
            {0.93f, 0.85f, 0.52f}, // Sand
            {0.2f, 0.6f, 0.2f},    // Grass
            {0.38f, 0.26f, 0.18f}, // Dirt
            {0.5f, 0.5f, 0.5f},    // Rock
            {0.95f, 0.95f, 0.95f}  // Snow
    };

    const std::vector terrainHeights = {
            0.0f, 0.1f, 0.13f, 0.2f, 0.8f, 0.9f, 1.0f
    };

    const std::vector<std::string> terrainTexturePaths = {
        "./src/textures/ocean_water.png",
        "./src/textures/water.png",
        "./src/textures/sand.jpg",
        "./src/textures/grass.jpg",
        "./src/textures/dirt.jpg",
        "./src/textures/rock.jpg",
        "./src/textures/snow.jpg"
    };

    const std::vector terrainMaterials = {
        waterMaterial,
        waterMaterial,
        sandMaterial,
        grassMaterial,
        dirtMaterial,
        rockMaterial,
        snowMaterial
    };

    const auto terrainTypeCount = static_cast<int>(terrainTexturePaths.size());

    const auto &meshRendererShader = mesh.renderer.shader;
    meshRendererShader->setInt("terrainTypeCount", terrainTypeCount);
    meshRendererShader->setFloatArray("terrainHeights", terrainHeights);
    meshRendererShader->setVec3Array("terrainColors", terrainColors);
    meshRendererShader->setMaterialArray("terrainMaterials", terrainMaterials);

    meshRendererShader->setFloatArray("heightRemapLUT", LUT);
    meshRendererShader->setInt("remapResolution", static_cast<int>(LUT.size()));

    meshRendererShader->setFloat("heightMin", 0.0f);
    meshRendererShader->setFloat("heightMax", 1.0f);

    for (const auto &path : terrainTexturePaths) {
        terrainTexturesIDs.push_back(create_opengl_texture(path, meshRendererShader->ID));
    }

    // Bind and inform shader about texture units
    for (int i = 0; i < terrainTypeCount; ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, terrainTexturesIDs[i]);
    }

    const GLint texLoc = glGetUniformLocation(meshRendererShader->ID, "terrainTextures");
    std::vector<GLint> units(terrainTypeCount);
    std::iota(units.begin(), units.end(), 0);
    glUniform1iv(texLoc, terrainTypeCount, units.data());
}

void PerlinPlane::draw(const glm::mat4 &vp, const Camera &camera) const {
    bindTerrainTextures(mesh.renderer.shader->ID, terrainTexturesIDs, "terrainTextures");

    const glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    const glm::mat4 mvp = vp * model;

    mesh.renderer.draw(mvp, camera);
}

