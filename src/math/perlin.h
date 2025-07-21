// yanked from wikipedia
#ifndef DONUT_PERLIN_H
#define DONUT_PERLIN_H

#include "material.h"

struct PerlinPlaneSettings {
    unsigned int sizeOfMesh;
    unsigned int meshResolution;
    float x_offset;
    float z_offset;
    float scale;
    int seed;
    float heightMultiplier;
    int octaves;
    float persistence;
    float lacunarity;

    bool operator!=(const PerlinPlaneSettings& other) const {
        return x_offset != other.x_offset || z_offset != other.z_offset|| seed != other.seed || sizeOfMesh != other.sizeOfMesh ||
               meshResolution != other.meshResolution || scale != other.scale ||
               heightMultiplier != other.heightMultiplier || octaves != other.octaves ||
               persistence != other.persistence || lacunarity != other.lacunarity;
    }
};

float perlin(float x, float y);
float perlinNoise(float x, float y, int seed, float scale = 1.0f, int octaves = 4, float persistence = 0.5f, float lacunarity = 2.0f);
void generatePermutation(int seed);

#endif
