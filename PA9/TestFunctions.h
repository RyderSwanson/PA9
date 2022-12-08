#pragma once
#include "header.h";
//**********************************
//all tests are designed to run inside of main game loop!!!
//**********************************
class TestFunctions {
public:
	/// <summary>
	/// test of the collision system (1 dimensional collision)
	/// </summary>
	/// <param name="playerY"></param>
	void testCollision(float& playerY) {
		static int num = -1;
		static int active = 0;
		if ((int)glfwGetTime() % 5 == 0 && active == 0) {
			active = 1;
			std::cout << "test";
			if (num == 0) playerY = 10;
			if (num == 1) playerY = -10;
			num++;
		}
		else if ((int)glfwGetTime() % 5 != 0 && active == 1) {
			active = 0;
		}
	}

	/// <summary>
	/// test of model loading system using assimp
	/// </summary>
	void testModelLoad() {
		Model cubeModel("Assets/cube/cube.obj");
	}

	/// <summary>
	/// test of shader loading system
	/// </summary>
	void testShaderLoad() {
		Shader shader("shader.vs", "shader.fs");
	}

	/// <summary>
	/// test of projection matrix creation and application
	/// </summary>
	/// <param name="shader"></param>
	void testProjectionMatrix(Shader shader) {
		shader.use();

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);

		shader.setMat4("projection", projection);
	}

	/// <summary>
	/// test of multiple lights inside of fragment shader
	/// </summary>
	/// <param name="shader"></param>
	void testFlashLight(Shader shader) {
		static int active = 0;
		if ((int)glfwGetTime() % 2 == 0 && active == 0) {
			shader.setVec3("flashLight.diffuse", glm::vec3(0));
			shader.setVec3("flashLight.specular", glm::vec3(0));
			active = 1;
		}
		else if ((int)glfwGetTime() % 2 != 0 && active == 1) {
			shader.setVec3("flashLight.diffuse", glm::vec3(1));
			shader.setVec3("flashLight.specular", glm::vec3(1));
			active = 0;
		}
	}
};