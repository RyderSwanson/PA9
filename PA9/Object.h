#pragma once

#include "ObjProto.h"

class Object : public ObjProto {
public:
	
	/// <summary>
	/// constructor, loads in all object data
	/// </summary>
	/// <param name="shader"></param>
	/// <param name="model"></param>
	/// <param name="location"></param>
	/// <param name="scale"></param>
	Object(Shader& shader, Model& model, glm::vec3 location, glm::vec3 scale);

	/// <summary>
	/// setup model matrix and draw object
	/// </summary>
	void draw();

	/// <summary>
	/// setters
	/// </summary>
	/// <param name="pos"></param>
	void setPos(glm::vec3 pos);
	void setScale(glm::vec3 scale);
};