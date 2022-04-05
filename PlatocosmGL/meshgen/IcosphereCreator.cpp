#include "IcosphereCreator.h"

IcosphereCreator::IcosphereCreator() {
	//Initialize icosahedron vertices and indices:
	addVertex(createVertex(-1, PHI, 0));
	addVertex(createVertex(1, PHI, 0));
	addVertex(createVertex(-1, -PHI, 0));
	addVertex(createVertex(1, -PHI, 0));

	addVertex(createVertex(0, -1, PHI));
	addVertex(createVertex(0, 1, PHI));
	addVertex(createVertex(0, -1, -PHI));
	addVertex(createVertex(0, 1, -PHI));

	addVertex(createVertex(PHI, 0, -1));
	addVertex(createVertex(PHI, 0, 1));
	addVertex(createVertex(-PHI, 0, -1));
	addVertex(createVertex(-PHI, 0, 1));

	addIndexTriplet(0, 5, 11);
	addIndexTriplet(0, 1, 5);
	addIndexTriplet(0, 7, 1);
	addIndexTriplet(0, 10, 7);
	addIndexTriplet(0, 11, 10);

	addIndexTriplet(1, 9, 5);
	addIndexTriplet(5, 4, 11);
	addIndexTriplet(11, 2, 10);
	addIndexTriplet(10, 6, 7);
	addIndexTriplet(7, 8, 1);

	addIndexTriplet(3, 4, 9);
	addIndexTriplet(3, 2, 4);
	addIndexTriplet(3, 6, 2);
	addIndexTriplet(3, 8, 6);
	addIndexTriplet(3, 9, 8);

	addIndexTriplet(4, 5, 9);
	addIndexTriplet(2, 11, 4);
	addIndexTriplet(6, 10, 2);
	addIndexTriplet(8, 7, 6);
	addIndexTriplet(9, 1, 8);
}

Vertex IcosphereCreator::createVertex(double x, double y, double z) {
					//coordinates		//normal			//color						//textureUVcoords
	double length = sqrt(x*x+y*y+z*z);
	x = x / length;
	y = y / length;
	z = z / length;
	return Vertex{ glm::vec3(x, y, z), glm::vec3(x, y, z), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) };
}

int IcosphereCreator::addVertex(Vertex vertex) {
	IcosphereCreator::meshVertices.push_back(vertex);
	return index++;
}

void IcosphereCreator::addIndexTriplet(GLuint p1, GLuint p2, GLuint p3) {
	IcosphereCreator::meshIndices.push_back(p1);
	IcosphereCreator::meshIndices.push_back(p2);
	IcosphereCreator::meshIndices.push_back(p3);
}

int IcosphereCreator::findMiddlePointIndex(int p1, int p2) {
	// first check if we have it already
	bool firstIsSmaller = p1 < p2;
	int smallerIndex = firstIsSmaller ? p1 : p2;
	int greaterIndex = firstIsSmaller ? p2 : p1;
	long int key = (smallerIndex << 16) + greaterIndex;

	//int ret;
	auto it = IcosphereCreator::midPointIndexCache.find(key);
	if (it != IcosphereCreator::midPointIndexCache.end())
	{
		return it->second;
	}

	// not in cache, calculate it
	Vertex point1 = IcosphereCreator::meshVertices[p1];
	Vertex point2 = IcosphereCreator::meshVertices[p2];
	Vertex middle = createVertex(
		(point1.position[0] + point2.position[0]) / 2.0,
		(point1.position[1] + point2.position[1]) / 2.0,
		(point1.position[2] + point2.position[2]) / 2.0);

	// add vertex makes sure point is on unit sphere
	int i = addVertex(middle);

	// store it, return index
	IcosphereCreator::midPointIndexCache.insert({ key, i });
	return i;
}

void IcosphereCreator::subdivide(int n) {
	if (detail > 7) {
		return;
	}
	detail++;
	for (int i = 0; i < n; i++)
	{
		std::vector<GLuint> faces2 = std::vector<GLuint>();
		for (int tristart = 0; tristart < IcosphereCreator::meshIndices.size(); tristart += 3)
		{
			// replace triangle by 4 triangles
			int v1 = IcosphereCreator::meshIndices[tristart];
			int v2 = IcosphereCreator::meshIndices[tristart+1];
			int v3 = IcosphereCreator::meshIndices[tristart+2];
			int a = findMiddlePointIndex(v1, v2);
			int b = findMiddlePointIndex(v2, v3);
			int c = findMiddlePointIndex(v3, v1);

			faces2.push_back(v1); faces2.push_back(a); faces2.push_back(c);
			faces2.push_back(v2); faces2.push_back(b); faces2.push_back(a);
			faces2.push_back(v3); faces2.push_back(c); faces2.push_back(b);
			faces2.push_back(a); faces2.push_back(b); faces2.push_back(c);
		}
		IcosphereCreator::meshIndices = faces2;
	}
}

void IcosphereCreator::perlinise(int seednum) {
	const siv::PerlinNoise::seed_type seed = seednum;

	const siv::PerlinNoise perlin{ seed };
	glm::vec3 newPosition;
	glm::vec3 normalinput;
	double x, y, z;
	glm::vec3 perlinvalue;
	glm::vec3 heightvalue;
	double c = 0.1;
	double d = 0.2;

	for (int i = 0; i < IcosphereCreator::meshVertices.size(); i++) {
		newPosition = IcosphereCreator::meshVertices[i].position;
		normalinput = IcosphereCreator::meshVertices[i].normal;
		x = normalinput[0];
		y = normalinput[1];
		z = normalinput[2];
		heightvalue = glm::vec3(0.0);
		for(int j = 0; j < 8; j++) {
			perlinvalue = glm::vec3(perlin.normalizedOctave3D((x * c * j), (y * c * j), (z * c * j), 4));
			heightvalue += glm::vec3(d) * normalinput * perlinvalue;
		}
		
		if (glm::length(newPosition + heightvalue) <= glm::length(glm::vec3(0.98) * newPosition)) {
			IcosphereCreator::meshVertices[i].position = glm::vec3(0.98) * newPosition;
		}
		else if (glm::length(newPosition + heightvalue) >= glm::length(glm::vec3(1.02) * newPosition)) {
			IcosphereCreator::meshVertices[i].position = glm::vec3(1.02) * newPosition;
		}
		else {
			IcosphereCreator::meshVertices[i].position += heightvalue;
		}

		//IcosphereCreator::meshVertices[i].position += heightvalue;
	}

	//prints:
		//printf("x = %.6f, y = %.6f, z = %.6f, perlinvalue = %.6f, %.6f, %.6f\n", x, y, z, perlinvalue.x, perlinvalue.y, perlinvalue.z);
		//printf("x = %.6f, y = %.6f, z = %.6f\n", IcosphereCreator::meshVertices[i].position.x, IcosphereCreator::meshVertices[i].position.y, IcosphereCreator::meshVertices[i].position.z);
		//printf("x = %.6f, y = %.6f, z = %.6f, value added = %.6f, %.6f, %.6f\n", IcosphereCreator::meshVertices[i].position.x, IcosphereCreator::meshVertices[i].position.y, IcosphereCreator::meshVertices[i].position.z, heightvalue.x, heightvalue.y, heightvalue.z);
}