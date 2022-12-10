#include "Monster.h"

Monster::Monster(Object* monster, irrklang::ISoundEngine* engine, glm::vec3 cameraFront, glm::vec3& playerPos) {
	this->monster = monster;
	this->playerPos = playerPos;
	this->engine = engine;
	sound = engine->play3D("Sounds/metalScrape.mp3", irrklang::vec3df(1,1,1), true, false, true);
	sound->setMinDistance(irrklang::ik_f32(5));
	engine->setSoundVolume(2);
	
	
}

int Monster::isLooking() {
	glm::vec3 ptom = glm::vec3(glm::normalize(playerPos - monster->position));
	if (glm::dot(ptom, cameraFront) < -glm::cos(glm::radians(35.5f))) {
		//std::cout << "looking" << std::endl;
		return 1;
	}
	return 0;
}

void Monster::checkCollision() {
	if (glm::distance(monster->position, playerPos) < 0.8) {
		exit(0);
	}
}

void Monster::move() {
	float movex = glm::normalize(playerPos - monster->position).x * 1 * deltaTime;
	float movez = glm::normalize(playerPos - monster->position).z * 1 * deltaTime;
	glm::vec3 move(movex, 0, movez);
	move *= glm::distance(monster->position, playerPos) / 10 + 1; //increase speed the further away monster is
	move *= glfwGetTime() / 30 + 1; //moves faster as game progresses
	monster->position += move;
}

void Monster::update(glm::vec3& playerPos, glm::vec3 cameraFront, double deltaTime, int flashlightOn) {
	this->playerPos = playerPos;
	this->cameraFront = cameraFront;
	this->deltaTime = deltaTime;
	irrklang::vec3df playerPosKlang(playerPos.x, playerPos.y, playerPos.z);
	irrklang::vec3df playerDir(-cameraFront.x, -cameraFront.y, -cameraFront.z);
	irrklang::vec3df monsterPos(monster->position.x, monster->position.y, monster->position.z);
	engine->setListenerPosition(playerPosKlang, playerDir);
	sound->setPosition(monsterPos);

	checkCollision();
	if (!isLooking() || !flashlightOn) {
		move();
		sound->setIsPaused(false);
	}
	else {
		sound->setIsPaused(true);
	}
}