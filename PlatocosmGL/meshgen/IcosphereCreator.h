#pragma once

#ifndef ICOSPHERE_CREATOR_CLASS_H
#define ICOSPHERE_CREATOR_CLASS_H
#include <math.h>
#include <map>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../infrastructure/datastructs.h"
#include "../noisegen/PerlinNoise.hpp"

class IcosphereCreator
{
private:
	std::map<long int, int> midPointIndexCache;
	int detail = 0;
	int index;
public:
	IcosphereCreator();

	std::vector<Vertex> meshVertices;
	std::vector<GLuint> meshIndices;

	Vertex createVertex(double x, double y, double z);
	int addVertex(Vertex vertex);
	void addIndexTriplet(GLuint p1, GLuint p2, GLuint p3);
	int findMiddlePointIndex(int p1, int p2);
	
	void subdivide(int n);

	void perlinise(int seed);
};

#endif