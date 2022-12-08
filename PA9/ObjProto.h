#pragma once

#include "Header.h"
#include "Shader.h"
#include "Model.h"

class ObjProto {
public:
	Shader* shader;
	Model* model;
	glm::vec3 position;
	glm::vec3 scale;

	//ObjProto() {}
	virtual void draw() = 0;
};