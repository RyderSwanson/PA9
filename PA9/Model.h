#pragma once

#include "Header.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
	/// <summary>
	/// constructor, immedietly load model
	/// </summary>
	/// <param name="path"></param>
	Model(std::string path) {
		loadModel(path);
	}

	/// <summary>
	/// runs mesh draw function
	/// </summary>
	/// <param name="shader"></param>
	void Draw(Shader& shader);

private:
	std::vector<Mesh> meshes;
	std::string dir;
	std::vector<Texture> textures_loaded;

	/// <summary>
	/// using assimp to load model
	/// </summary>
	/// <param name="path"></param>
	void loadModel(std::string path);

	/// <summary>
	/// recusivley load meshes
	/// </summary>
	/// <param name="node"></param>
	/// <param name="scene"></param>
	void processNode(aiNode* node, const aiScene* scene);

	/// <summary>
	/// using assimp to load all model info into corresponding vectors
	/// </summary>
	/// <param name="mesh"></param>
	/// <param name="scene"></param>
	/// <returns></returns>
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	/// <summary>
	/// load textures into vectors using assimp
	/// </summary>
	/// <param name="mat"></param>
	/// <param name="type"></param>
	/// <param name="typeName"></param>
	/// <returns></returns>
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

// load texture from file then load into opengl
unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = 0);