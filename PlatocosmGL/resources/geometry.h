#pragma once
#include <cstdint>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
//#include "../infrastructure/VBO.h"
#include "../infrastructure/datastructs.h"


GLfloat triforceVertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3,      -0.05f,    // Lower left corner 1
    0.5f, -0.5f * float(sqrt(3)) / 3,       -0.05f,     // Lower right corner 1
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3,    -0.05f,  // Upper corner 1
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6,   -0.05f, // Inner left 1
    0.5f / 2, 0.5f * float(sqrt(3)) / 6,    -0.05f,  // Inner right 1
    0.0f, -0.5f * float(sqrt(3)) / 3,       -0.05f,      // Inner down 1

    -0.5f, -0.5f * float(sqrt(3)) / 3,      0.05f,    // Lower left corner 2
    0.5f, -0.5f * float(sqrt(3)) / 3,       0.05f,     // Lower right corner 2
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3,    0.05f,  // Upper corner 2
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6,   0.05f, // Inner left 2
    0.5f / 2, 0.5f * float(sqrt(3)) / 6,    0.05f,  // Inner right 2
    0.0f, -0.5f * float(sqrt(3)) / 3,       0.05f,      // Inner down 2
};

GLuint triforceIndices[] =
{
    0, 3, 5,    // Lower left triangle 1
    3, 2, 4,    // Lower right triangle 1
    5, 4, 1,     // Upper triangle 1

    6, 9, 11,    // Lower left triangle 2
    9, 10, 8,    // Lower right triangle 2
    11, 10, 7,     // Upper triangle 2

    1, 2, 8,
    1, 8, 7,
    1, 7, 6,
    1, 6, 0,
    6, 8, 2,
    6, 2, 0,

    5, 4, 10,
    5, 10, 11,
    4, 3, 9,
    4, 9, 10,
    9, 3, 5,
    9, 5, 11,
};

std::vector<Vertex> spherePrimeVertices =
{ //               COORDINATES            /            Normals             /           Color            /       TexCoord      //
    Vertex{glm::vec3(0,  PHI,  1),       glm::vec3(0,  PHI,  1),    glm::vec3(1.0f, 1.0f, 1.0f),    glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(0, -PHI,  1),       glm::vec3(0, -PHI,  1),    glm::vec3(0.0f, 1.0f, 1.0f),    glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(0,  PHI, -1),       glm::vec3(0,  PHI, -1),    glm::vec3(0.0f, 0.0f, 1.0f),    glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(0, -PHI, -1),       glm::vec3(0, -PHI, -1),    glm::vec3(1.0f, 1.0f, 0.0f),    glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(1,  0,  PHI),       glm::vec3(1,  0,  PHI),    glm::vec3(1.0f, 0.0f, 0.0f),    glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-1, 0,  PHI),       glm::vec3(-1, 0,  PHI),    glm::vec3(1.0f, 0.0f, 1.0f),    glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(1,  0, -PHI),       glm::vec3(1,  0, -PHI),    glm::vec3(1.0f, 1.0f, 1.0f),    glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-1, 0, -PHI),       glm::vec3(-1, 0, -PHI),    glm::vec3(1.0f, 1.0f, 1.0f),    glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(PHI,   1,  0),      glm::vec3(PHI,   1,  0),    glm::vec3(1.0f, 1.0f, 1.0f),    glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(PHI,  -1,  0),      glm::vec3(PHI,  -1,  0),    glm::vec3(1.0f, 1.0f, 1.0f),    glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-PHI,  1,  0),      glm::vec3(-PHI,  1,  0),    glm::vec3(1.0f, 1.0f, 1.0f),    glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-PHI, -1,  0),      glm::vec3(-PHI, -1,  0),    glm::vec3(1.0f, 1.0f, 1.0f),    glm::vec2(0.0f, 0.0f)},
};

std::vector<GLuint> spherePrimeIndices =
{
    0, 5, 4,
    0, 4, 8,
    0, 8, 2,
    0, 2, 10,
    0, 10, 5,
    3, 9, 1,
    3, 1, 11,
    3, 11, 7,
    3, 7, 6,
    3, 6, 9,
    1, 9, 4,
    4, 9, 8,
    8, 9, 6,
    8, 6, 2,
    2, 6, 7,
    2, 7, 10,
    7, 11, 10,
    11, 5, 10,
    11, 1, 5,
    1, 4, 5,
};