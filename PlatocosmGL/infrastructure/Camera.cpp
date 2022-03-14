#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, SDL_Window* window) {
	Camera::width = width;
	Camera::height = height;
	Camera::window = window;
	Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(std::vector<int> keyEvents) {
	for (int i = 0; i < keyEvents.size(); i++) {
		if (keyEvents[i] != 0) { Action(i, keyEvents[i]); }
	}

	if (cameraMode == 1) {
		SDL_SetRelativeMouseMode(SDL_TRUE);

		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-(sensitivity * keyEvents[11]) / width), glm::normalize(glm::cross(Orientation, Up)));
		if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) or (glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))) {
			Orientation = newOrientation;
		}
		Orientation = glm::rotate(Orientation, glm::radians(-(sensitivity * keyEvents[10]) / height), Up);
	}
	else {
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
}



//Up, Down, Left, Right, Space, Ctrl, W, A, S, D
void Camera::Action(int action, int data) {
	switch (action) {
	case 0:
		Position += speed * Orientation;
		break;
	case 1:
		Position += speed * -Orientation;
		break;
	case 2:
		Position += speed * -glm::cross(Orientation,Up);
		break;
	case 3:
		Position += speed * glm::cross(Orientation, Up);
		break;
	case 4:
		Position += speed * Up;
		break;
	case 5:
		Position += speed * -Up;
		break;
	case 6:
		Position += speed * Orientation;
		break;
	case 7:
		Position += speed * -glm::cross(Orientation, Up);
		break;
	case 8:
		Position += speed * -Orientation;
		break;
	case 9:
		Position += speed * glm::cross(Orientation, Up);
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		Up = glm::rotate(Up, (-glm::radians(20.0f) / height), Orientation);
		break;
	case 13:
		Up = glm::rotate(Up, (glm::radians(20.0f) / height), Orientation);
		break;
	case 14:
		Up = glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	case 15:
		if (cameraMode) { cameraMode = 0; }
		else { cameraMode = 1; }
		break;
	default:
		break;
	}
}