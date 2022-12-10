#pragma once

#include "Object.h"

class Objective {
public:
	Objective(Shader* shader, Object* goalObject, irrklang::ISoundEngine* engine, glm::vec3& playerPos);

	void respawn();
	void checkCollision();
	void update(glm::vec3& playerPos, double deltaTime);

	Shader* shader;
	Object* goalObject;
	irrklang::ISoundEngine* engine;
	irrklang::ISound* sound;
	glm::vec3 playerPos;
	int numCollected;
};