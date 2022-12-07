#pragma once

#include "Header.h"
#include "Shader.h"

class ObjProto {
public:
	Shader shader;
	glm::vec3 position;
	glm::vec3 scale;

	//ObjProto() {}
	virtual void draw() = 0;
};