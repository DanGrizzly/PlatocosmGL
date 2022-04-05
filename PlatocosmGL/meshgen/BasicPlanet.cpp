#include "BasicPlanet.h"

BasicPlanet::BasicPlanet(int seed, glm::vec3 position, glm::vec3 color, float scale, int detail, int framesPerRot) {
	BasicPlanet::color = color;
	BasicPlanet::scale = scale;
	BasicPlanet::position = position;

	IcosphereCreator icospherecreator = IcosphereCreator();
	icospherecreator.subdivide(detail);
	icospherecreator.perlinise(seed);

	std::vector<Texture> noTextures = std::vector<Texture>();

	BasicPlanet::planetMesh = Mesh(icospherecreator.meshVertices, icospherecreator.meshIndices, noTextures, position, scale);

	BasicPlanet::planetMesh.framesPerRot = framesPerRot;
}

void BasicPlanet::Draw(Shader& shader, Camera& camera) {

	glUniform1f(glGetUniformLocation(shader.ID, "planetScale"), scale);
	glUniform3f(glGetUniformLocation(shader.ID, "planetColor"), color.x, color.y, color.z);
	BasicPlanet::planetMesh.Draw(shader, camera);
}