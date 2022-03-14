#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL.h>
#include <SDL_opengl.h>

class BackendHolder
{
public:
	SDL_Window* window;
	SDL_GLContext context;

	int window_width, window_height;

	//Up, Down, Left, Right, Space, Ctrl, W, A, S, D, 10:xrel, 11:yrel, Q, E, R, C, F
	std::vector<int> events = std::vector<int>(18, 0);

	BackendHolder(GLuint window_width, GLuint window_height);
	void handleEvents(bool* quit);
	void refreshScreen();
	void FreeAndQuit();
};