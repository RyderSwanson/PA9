#include "Object.h"

Object::Object(Shader shader, glm::vec3 location, glm::vec3 scale) {
	this->shader = shader;
	this->position = location;
	this->scale = scale;
}

void Object::draw() {

}