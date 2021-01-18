#include "../glad/glad.h"
#include "Window.h"
#include <iostream>
#include "../shader/Shader.hpp"
#include "../vertexinput/VertexInput.h"
#include <ctime>
#include <cstdlib>
#include "../texture/Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../camera/Camera.hpp"

float mixValue = 0.2f;

Camera camera(glm::vec3(0.0f, 5.0f, 20.0f));

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallBack(GLFWwindow* window, double xpos, double ypos);
void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset);

Window::Window() {
	camera.mousePosition(WIDTH, HEIGHT);
	initWindow();
	createWindow();
}

void Window::update(){

    Shader earthShader("./light/earth.vs", "./light/earth.fs");
    Shader sunShader("./light/sun.vs", "./light/sun.fs");

	VertexInput vertex;

	glm::vec3 cubePositions[] = {
			//middle
			glm::vec3(0.0f,  0.0f,  0.0f),
			//horizontal positive
			glm::vec3(0.0f,  1.2f,  0.0f),
			glm::vec3(0.0f,  2.3f,  0.0f),
			glm::vec3(0.0f,  3.4f,  0.0f),
			//horizontal negative
			glm::vec3(0.0f,  -1.2f,  0.0f),
			glm::vec3(0.0f,  -2.3f,  0.0f),
			glm::vec3(0.0f,  -3.4f,  0.0f),
			//vertical positive at right
			glm::vec3(1.2f,  0.0f,  0.0f),
			glm::vec3(2.3f,  0.0f,  0.0f),
			glm::vec3(3.4f,  0.0f,  0.0f),
			//vertical negative at left
			glm::vec3(-1.2f,  0.0f,  0.0f),
			glm::vec3(-2.3f,  0.0f,  0.0f),
			glm::vec3(-3.4f,  0.0f,  0.0f),
	};

	earthShader.use();
	earthShader.setInt("earthTexture", 0);
	sunShader.use();
	sunShader.setInt("sunTexture", 1);

	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(window)){
		camera.calcDeltaTime();

		processInput(window);

		glClearColor(0.2f,0.4f,0.5f,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.setCamera(earthShader, sunShader);
		vertex.update(earthShader, sunShader, cubePositions);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vertex.deleteVertexAndBuffers();
	glfwTerminate();

}

void Window::initWindow(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for OS X
}

int Window::createWindow(){
	window = glfwCreateWindow(WIDTH,HEIGHT, "Learn OpenGL", NULL, NULL);

	if(window == NULL){
		std::cout<<"Failed to create GLFW window!"<< std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	//cursor and scroll callback
	glfwSetCursorPosCallback(window, mouseCallBack);
	glfwSetScrollCallback(window, scrollCallBack);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout<<"Failed to init GLAD"<<std::endl;
		return -1;
	}

	update();

	return 0;
}

void Window::processInput(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	camera.processkeyboard(window);

	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		mixValue += 0.005f;
		if(mixValue >= 1.0f)
			mixValue = 1.0f;
	}

	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		mixValue -= 0.005f;
		if(mixValue <= 0.0f)
			mixValue = 0.0f;
	}
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height){
	glViewport(0,0, width, height);
}

void mouseCallBack(GLFWwindow* window, double xpos, double ypos){
	camera.mouseCallBack(window, xpos, ypos);
}

void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset){
	camera.scrollCallBack(window, xOffset, yOffset);
}

Window::~Window() {

}

