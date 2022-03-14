#pragma once
#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	VAO VAO;

	Mesh(std::vector<Vertex>& vertices, std::vector <GLuint>& indices, std::vector<Texture>& textures);

	void Draw(Shader& shader, Camera& camera);
	void ChangeMesh(std::vector<Vertex>& vertices, std::vector <GLuint>& indices, std::vector<Texture>& textures);
	void Update();
};

#endif