#include "Objective.h"

Objective::Objective(Shader* shader, Object* goalObject, irrklang::ISoundEngine* engine, glm::vec3& playerPos) {
	this->shader = shader;
	this->goalObject = goalObject;
	this->playerPos = playerPos;
	numCollected = 0;
	this->engine = engine;
}

void Objective::respawn() {
	glm::vec3 newpos(rand() % 50 - 25, -1, rand() % 50 - 25);
	goalObject->position = newpos;
	shader->use();
	shader->setVec3("pointLights[0].position", newpos);
	
}

void Objective::checkCollision(float& batteryLevel) {
	if (glm::distance(goalObject->position, playerPos) < 1) {
		respawn();
		batteryLevel += .7;
		numCollected++;
		engine->play2D("Sounds/pickup.mp3", false);
		std::cout << "Point collected, now at: " << numCollected << std::endl;
	}
}

void Objective::update(glm::vec3& playerPos, float& batteryLevel, double deltaTime) {
	this->playerPos = playerPos;
	checkCollision(batteryLevel);
	goalObject->scale = glm::vec3((((glm::sin(glfwGetTime() * 2) + 1) / 2) * .02) + .1);
}