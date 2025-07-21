#ifndef PERLIN_MESH_H
#define PERLIN_MESH_H

#include "glad_include.h"
#include <vector>

class PerlinMesh {
public:
    int square_length;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    explicit PerlinMesh(const struct PerlinPlaneSettings &settings);
};


#endif // PERLIN_MESH_H
