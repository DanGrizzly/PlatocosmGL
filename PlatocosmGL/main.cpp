#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "OpenGL32.lib" )

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "infrastructure/BackendHolder.h"
#include "infrastructure/Mesh.h"
#include "infrastructure/Camera.h"

#include "resources/geometry.h"

#include "meshgen/IcosphereCreator.h"

#include "noisegen/PerlinNoise.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

int main(int argc, char* argv[]) {
	BackendHolder theBackend = BackendHolder(SCREEN_WIDTH, SCREEN_HEIGHT);

	//GL settings
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Create shaders
	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

	//Create textures;
	std::vector<Texture> noTextures = std::vector<Texture>();

	//Create Mesh objects
	//Mesh icosphere(spherePrimeVertices, spherePrimeIndices, noTextures);
	IcosphereCreator icospherecreator = IcosphereCreator();
	printf("Primitives in scene: Vertices: %d, Faces: %d\n", icospherecreator.meshVertices.size(), icospherecreator.meshIndices.size() / 3);
	Mesh icosphere(icospherecreator.meshVertices, icospherecreator.meshIndices, noTextures);

	icosphere.vertices[0].position[0] = 2 * icosphere.vertices[0].position[0];
	icosphere.Update();

	//Uniforms
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "frame");

	//Activate shaders
	shaderProgram.Activate();


	//IMPLEMENT LIGHTING TO BE DONE WITH THIS...
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(5.0f, 0.0f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	//shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	//...


	//Draw the screen background
	//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClearColor(0.07f, 0.03f, 0.06f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	theBackend.refreshScreen();
	
	//Create cameras
	Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f), theBackend.window);

	//Main loop
	bool quit = false;
	unsigned int counter = 0;
	while (!quit) {

		//Input events
		theBackend.handleEvents(&quit);
		if (theBackend.events[17] == 1) {
			printf("Subdividing...\n");
			icospherecreator.subdivide(1);
			icosphere.ChangeMesh(icospherecreator.meshVertices, icospherecreator.meshIndices, noTextures);
		}

		//Send uniforms
		glUniform1f(uniID, fmod(counter / 200.0, (2.0*PI)));

		//Apply camera changes
		camera.Inputs(theBackend.events);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		//The drawing:
		icosphere.Draw(shaderProgram, camera);
		
		//Refresh frame
		theBackend.refreshScreen();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		counter++;
	}

	//The deleting:
	shaderProgram.Delete();

	//Quit:
	theBackend.FreeAndQuit();
	return 0;
}