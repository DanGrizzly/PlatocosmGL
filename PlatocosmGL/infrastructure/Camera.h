#pragma once
#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <vector>
#include <GL/glew.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera {
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	SDL_Window* window;

	int cameraMode = 1;

	int width;
	int height;

	float speed = 0.02f;
	float sensitivity = 100.0f;

	Camera(int width, int height, glm::vec3 position, SDL_Window* window);

	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	void Inputs(std::vector<int> keyEvents);
	void Action(int action, int data);
};

#endif