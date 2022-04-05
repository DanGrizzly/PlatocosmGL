#pragma once

#include "../infrastructure/Mesh.h"
#include "IcosphereCreator.h"


class BasicPlanet
{
public:
	Mesh planetMesh;// = Mesh(std::vector<Vertex>(), std::vector<GLuint>(), std::vector<Texture>(), glm::vec3(0.0f));
	//IcosphereCreator icosphere;

	int seed;
	float scale;
	int detail;
	glm::vec3 position;
	glm::vec3 color;

	BasicPlanet(int seed, glm::vec3 position, glm::vec3 color = glm::vec3(0.5f, 0.4f, 0.0f), float scale = 1.0f, int detail = 5, int framesPerRot = 5000);

	void Draw(Shader& shader, Camera& camera);
};

//BasicPlanet::BasicPlanet(int seed, float scale = 1.0f, int detail = 1) 
//	: planetMesh(vertices, indices, textures, position) {}