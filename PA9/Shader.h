#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {
public:
	unsigned int ID;
	unsigned int vertex;
	unsigned int fragment;

	/// <summary>
	/// constructor, handles loading shaders into opengl
	/// </summary>
	/// <param name="vertexPath"></param>
	/// <param name="fragmentPath"></param>
	Shader(const char* vertexPath, const char* fragmentPath);

	/// <summary>
	/// set as current shader
	/// </summary>
	void use();

	/// <summary>
	/// All setters for loading variables into graphics card
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
};



