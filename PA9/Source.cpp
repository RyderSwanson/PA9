#include "Header.h"

#include "Shader.h"

#include "Model.h"

#include "Object.h"

#define numAvgFrames 60

bool firstMouse = 1;
bool pause = 0;
bool fullscreen = 0;

int width, height;

double currentFrame;
double deltaTime = 0.0f;
double lastFrame = 0.0f;
double frameTimeBuffer[numAvgFrames] = { 0 };
int timeSec = 0;

float yaw = -90.0f, pitch = 0.0f;
float lastX, lastY;

glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 lightPos = glm::vec3(1, 8, 1);


//using namespace std;
void glfwFrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void getInput(GLFWwindow* window);
unsigned int loadTexture(const char* filePath);
void setProjection(Shader theShader, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
GLFWwindow* createWindow(int width, int height, const char* name, int fullscreen);
void fps(double deltaTime, double time);

int main(void) {
	unsigned int VBO;
	unsigned int VAO;
	unsigned int lightVAO;
	unsigned int EBO;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;




	std::cout << "***" << std::endl;

	//stbi
	stbi_set_flip_vertically_on_load(true);

	//glfw initial settings
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//creating a window object
	GLFWwindow* window = createWindow(600, 600, "PA9", 0);


	//turn on glad (so we can use opengl)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//setting opengl viewport size
	Shader theShader("dirLight.vs", "dirLight.fs");
	Shader lightingShader("lightingShader.vs", "lightingShader.fs");
	glViewport(0, 0, 600, 600);

	

	//background color, should be black
	glClearColor(0.005, 0.0, 0.01, 1);

	//vsync
	glfwSwapInterval(1);


	//cube
	theShader.use();

	//matricies for 3d
	glm::mat4 model = glm::mat4(1.0f);


	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	theShader.setMat4("model", model);
	theShader.setMat4("view", view);

	glfwGetFramebufferSize(window, &width, &height);
	setProjection(theShader, width, height);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);

	lastX = width / 2;
	lastY = height / 2;

	theShader.setInt("light.type", 0);

	theShader.setVec3("light.ambient", glm::vec3(1));
	theShader.setVec3("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	theShader.setVec3("light.specular", glm::vec3(1.0f));
	theShader.setVec3("light.direction", glm::vec3(0.0f, -1.0f, 0.0f));
	theShader.setVec3("light.position", lightPos);

	theShader.setFloat("light.constant", 0.01f);
	theShader.setFloat("light.linear", 0.09f);
	theShader.setFloat("light.quadratic", 0.032f);


	theShader.setFloat("material.shininess", 32.0f);

	//flashlight stuff
	//theShader.setVec3("light.position", cameraPos);
	//theShader.setVec3("light.direction", cameraFront);
	theShader.setFloat("light.cutOff", glm::cos(glm::radians(25.5f)));
	theShader.setFloat("light.outerCutOff", glm::cos(glm::radians(30.5f)));


	theShader.setVec3("viewPos", cameraPos);


	//light cube
	lightingShader.use();

	lightingShader.setMat4("model", model);
	lightingShader.setMat4("view", view);
	setProjection(lightingShader, width, height);
	lightingShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
	lightingShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	
	//test model loading
	Model test("Assets/backpack/backpack.obj");
	Object obj(theShader, test, glm::vec3(0, 0, 0), glm::vec3(1,1,1));

	//Model icoModel("Assets/ico/ico.obj");
	//Object ico(theShader, icoModel, glm::vec3(3, 0, 0), glm::vec3(1, 1, 1));

	//light cube
	Model cubeModel("Assets/cube/cube.obj");
	Object cube(lightingShader, cubeModel, lightPos, glm::vec3(0.3f));

	//main game loop
	while (!glfwWindowShouldClose(window)) {

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		fps(deltaTime, currentFrame);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		getInput(window);

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		theShader.use();


		//flashlightstuff
		//theShader.setVec3("light.position", cameraPos);
		//theShader.setVec3("light.direction", cameraFront);

		//ghetto projection matrix resetting for full screen
		glfwGetFramebufferSize(window, &width, &height);
		setProjection(theShader, width, height);

		theShader.setMat4("view", view);
		theShader.setVec3("viewPos", cameraPos);

		lightingShader.use();
		setProjection(lightingShader, width, height);
		lightingShader.setMat4("view", view);

		//int currentTime = time(NULL);

		obj.draw();
		//ico.draw();
		cube.draw();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

void glfwFrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void getInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	const float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	
}

unsigned int loadTexture(const char* filePath) {

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "image failed to load: " << filePath << std::endl;
	}

	stbi_image_free(data);

	return texture;
}

void setProjection(Shader theShader, int width, int height) {
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(90.0f), (float)width / (float)height, 0.1f, 100.0f);

	theShader.setMat4("projection", projection);

}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {


	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = 0;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	//std::cout << pitch << std::endl;
	//std::cout << yaw << std::endl;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

}

//runs once per key press
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		if (pause) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			pause = 0;
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			pause = 1;
		}
	}

	if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
		GLFWmonitor* monitor = glfwGetWindowMonitor(window);
		//was in windowed mode
		if (monitor == NULL) {
			monitor = glfwGetPrimaryMonitor();
		}
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		if (!fullscreen) {
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			glfwSwapInterval(1);
			fullscreen = 1;
		}
		else {
			glfwSetWindowMonitor(window, NULL, 100, 100, 600, 600, 0);
			fullscreen = 0;
		}
	}
}

GLFWwindow* createWindow(int width, int height, const char* name, int fullscreen) {
	GLFWwindow* window;
	

	window = glfwCreateWindow(width, height, name, NULL, NULL);

	//check if window object worked
	if (window == NULL) {
		std::cout << "Busted window" << std::endl;
		glfwTerminate();
		exit(101);
	}


	//assign window object as the one or something
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, glfwFrameBufferSizeCallback);

	glfwSetCursorPosCallback(window, mouseCallback);

	glfwSetKeyCallback(window, keyCallback);

	return window;
}

void fps(double deltaTime, double time) {
	double frameFps = 1.0 / deltaTime;

	for (int i = 0; i < numAvgFrames - 1; i++) {
		frameTimeBuffer[i] = frameTimeBuffer[i + 1];
	}

	frameTimeBuffer[numAvgFrames - 1] = frameFps;

	if (timeSec != (int)time) {
		double avg = 0;
		std::cout << std::endl;
		std::cout << "cur: " << frameFps << std::endl;

		for (int i = 0; i < numAvgFrames; i++) {
			avg += frameTimeBuffer[i];
		}
		avg /= numAvgFrames;
		std::cout << "avg: " << avg << std::endl;

		timeSec = (int)time;
	}
	//std::cout << "arr: ";
	//for (int i = 0; i < 5; i++) {
	//	std::cout << lastFiveFrames[i] << ", ";
	//}
	//std::cout << std::endl;

}