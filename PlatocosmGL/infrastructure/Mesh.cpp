#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector <GLuint>& indices, std::vector<Texture>& textures, glm::vec3 position, float scale) {
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	Mesh::objectPos = position;
	Mesh::objectScale = scale;

	//set initial object model transformations
	glm::mat4 Transmat = glm::translate(glm::mat4(1.0f), objectPos);
	glm::mat4 Scalemat = glm::scale(glm::mat4(1.0f), glm::vec3(objectScale));
	glm::mat4 Rotmat = glm::mat4(1.0f); 
	if (objectTilt != glm::vec3(0.0f, 1.0f, 0.0f)) {
		if (objectTilt == glm::vec3(0.0f, -1.0f, 0.0f)) {
			Rotmat = glm::rotate(glm::mat4(1.0f), float(PI), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else {
			Rotmat = glm::rotate(glm::mat4(1.0f), glm::angle(glm::vec3(0.0f, 1.0f, 0.0f), objectTilt), glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), objectTilt)));
		}
	}
	objectModel = Transmat * Scalemat * Rotmat;



	VAO.Bind();
	VBO VBO(vertices);
	EBO EBO(indices);

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)(0));
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera) {
	
	//get object model transformations
	objectPos += velocity;

	glm::mat4 Transmat = glm::translate(glm::mat4(1.0f), velocity);
	glm::mat4 Scalemat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
	glm::mat4 Rotmat = glm::rotate(objectModel, glm::radians(360 / framesPerRot), glm::vec3(0.0f, 1.0f, 0.0f));
	objectModel = Transmat * Scalemat * Rotmat;
	
	shader.Activate();
	VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++) {
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse") {
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular") {
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
	//Send model transformations to shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	//Send object position to shader
	glUniform3fv(glGetUniformLocation(shader.ID, "objpos"), 1, glm::value_ptr(objectPos));



	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::ChangeMesh(std::vector<Vertex>& vertices, std::vector <GLuint>& indices, std::vector<Texture>& textures) {
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	VAO.Bind();
	VBO VBO(vertices);
	EBO EBO(indices);

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)(0));
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Update() {
	VAO.Bind();
	VBO VBO(vertices);
	EBO EBO(indices);

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)(0));
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}
