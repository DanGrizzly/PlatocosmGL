#include "BackendHolder.h"

BackendHolder::BackendHolder(GLuint window_width, GLuint window_height) {
	BackendHolder::window_width = window_width;
	BackendHolder::window_height = window_height;

	//Initialising SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1); //1 for use VSync, 0 for no Vsync.

	window = SDL_CreateWindow("SDL_GL: Platocosm", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	context = SDL_GL_CreateContext(window);
	if (context == NULL) { printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError()); exit(1); }

	SDL_GL_MakeCurrent(window, context);

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) { printf("Error initializing GLEW!\n"); exit(1); }

	printf("Status: Using GL %s\n", glGetString(GL_VERSION));
}

void BackendHolder::handleEvents(bool* quit) {

	events[10] = 0; //xrel
	events[11] = 0; //yrel
	events[14] = 0; //R, reset Up
	events[15] = 0; //C, camera mode
	//events[16] is for F, toggles wireframe mode on KEYUP
	events[17] = 0; //I, increase icosphere detail?

	SDL_Event e;
	while (SDL_PollEvent(&e) > 0) {
		switch (e.type) {
		case SDL_QUIT:
			*quit = true;
			break;
		case SDL_MOUSEMOTION:
			events[10] = e.motion.xrel;
			events[11] = e.motion.yrel;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_UP:
				events[0] = 1;
				break;
			case SDLK_DOWN:
				events[1] = 1;
				break;
			case SDLK_LEFT:
				events[2] = 1;
				break;
			case SDLK_RIGHT:
				events[3] = 1;
				break;
			case SDLK_SPACE:
				events[4] = 1;
				break;
			case SDLK_LCTRL:
				events[5] = 1;
				break;
			case SDLK_w:
				events[6] = 1;
				break;
			case SDLK_a:
				events[7] = 1;
				break;
			case SDLK_s:
				events[8] = 1;
				break;
			case SDLK_d:
				events[9] = 1;
				break;
			case SDLK_q:
				events[12] = 1;
				break;
			case SDLK_e:
				events[13] = 1;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
			case SDLK_UP:
				events[0] = 0;
				break;
			case SDLK_DOWN:
				events[1] = 0;
				break;
			case SDLK_LEFT:
				events[2] = 0;
				break;
			case SDLK_RIGHT:
				events[3] = 0;
				break;
			case SDLK_SPACE:
				events[4] = 0;
				break;
			case SDLK_LCTRL:
				events[5] = 0;
				break;
			case SDLK_w:
				events[6] = 0;
				break;
			case SDLK_a:
				events[7] = 0;
				break;
			case SDLK_s:
				events[8] = 0;
				break;
			case SDLK_d:
				events[9] = 0;
				break;
			case SDLK_q:
				events[12] = 0;
				break;
			case SDLK_e:
				events[13] = 0;
				break;
			case SDLK_r:
				events[14] = 1;
				break;
			case SDLK_c:
				events[15] = 1;
				break;
			case SDLK_f:
				if (events[16]) { events[16] = 0; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);}
				else { events[16] = 1; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);}
				break;
			case SDLK_i:
				events[17] = 1;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void BackendHolder::refreshScreen() {
	SDL_GL_SwapWindow(window);
}

void BackendHolder::FreeAndQuit() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}