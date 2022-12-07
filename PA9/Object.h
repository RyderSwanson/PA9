#pragma once

#include "ObjProto.h"

class Object : public ObjProto {
public:
	Object(Shader shader, glm::vec3 location, glm::vec3 scale);
	void draw();
};