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

	glm::mat4 objectModel = glm::mat4(1.0f);
	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 objectTilt = glm::vec3(0.0f, 1.0f, 0.0f);
	float objectScale = 1.0f;
	
	glm::vec3 velocity = glm::vec3(0.0f, 0.01f, 0.00f);
	float framesPerRot = 5000;

	VAO VAO;

	Mesh(std::vector<Vertex>& vertices, std::vector <GLuint>& indices, std::vector<Texture>& textures, glm::vec3 position, float scale);
	Mesh() = default;

	void Draw(Shader& shader, Camera& camera);
	void ChangeMesh(std::vector<Vertex>& vertices, std::vector <GLuint>& indices, std::vector<Texture>& textures);
	void Update();
};

#endif