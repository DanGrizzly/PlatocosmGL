#pragma once
#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <GL/glew.h>
#include "stb_image.h"

#include "shaderClass.h"

class Texture
{
public:
	GLuint ID;
	const char* type;
	GLuint unit;

	Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
};

#endif

//Texture guide:
	//Prior to main loop: 
	//GLuint uniTex0ID = glGetUniformLocation(shaderProgram.ID, "tex0");
	//glUniform1i(uniTex0ID, 0);
	//Texture begCat("resources/textures/begging_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//begCat.texUnit(shaderProgram, "tex0", 0);
	//
	//Each loop:
		//begCat.Bind();
	//At the end:
	//begCat.Delete();