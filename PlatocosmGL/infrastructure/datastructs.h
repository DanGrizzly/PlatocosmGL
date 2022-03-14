#pragma once
#include <glm/glm.hpp>

#define PHI 1.61803398875
#define PI 3.14159265359

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
};

struct TriangleIndices {
    int p1, p2, p3;
};