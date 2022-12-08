#include "Object.h"

Object::Object(Shader& shader, Model& model, glm::vec3 location, glm::vec3 scale) {
	this->shader = &shader;
	this->model = &model;
	this->position = location;
	this->scale = scale;
}

void Object::draw() {
	shader->use();

	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::scale(modelMat, scale);
	modelMat = glm::translate(modelMat, position);
	shader->setMat4("model", modelMat);

	model->Draw(*shader);
}