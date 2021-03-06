#pragma once
#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../infrastructure/datastructs.h"

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vertex>& vertices);

	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif