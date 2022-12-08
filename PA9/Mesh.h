#pragma once

#include "Header.h"
#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	/// <summary>
	/// setup mesh variables
	/// </summary>
	/// <param name="vertices"></param>
	/// <param name="indices"></param>
	/// <param name="textures"></param>
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	/// <summary>
	/// activate textures and vertex array, then draw with opengl
	/// </summary>
	/// <param name="shader"></param>
	void Draw(Shader& shader);

private:
	unsigned int VAO, VBO, EBO;
	
	/// <summary>
	/// load all mesh data into opengl
	/// </summary>
	void setupMesh();
};