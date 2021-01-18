#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "VertexInput.h"
#include <iostream>
#include "../shader/Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
#include "../camera/Camera.hpp"
#include "../texture/Texture.h"

Texture texture;

VertexInput::VertexInput() {
	insertVertexData();
	texture.loadTexture();
}

void VertexInput::insertVertexData(){



	float vertices[] = {
	    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

		unsigned int indices[] = {
			0,1,3,
			1,2,3
		};

		//earth
		glGenVertexArrays(1, &earthVAO);
		glGenBuffers(1, &earthVBO);
		glBindVertexArray(earthVAO);
		glBindBuffer(GL_ARRAY_BUFFER, earthVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);

		//sun
		glGenVertexArrays(1, &sunVAO);
		glGenBuffers(1, &sunVBO);
		glBindVertexArray(sunVAO);
		glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
		glBindVertexArray(0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}

void VertexInput::update(Shader earthShader, Shader sunShader, glm::vec3 cubePositions[]){

	texture.transformTexture(earthShader, sunShader);

	earthShader.use();
    glBindVertexArray(earthVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getEarthTexture());
    earthShader.setVec3("earthColor", glm::vec3(0.31f, 0.5f, 1.0f));
    earthShader.setVec3("lightColor", glm::vec3(1.0f));
    earthShader.setVec3("lightPos", sunOrigin);
    glm::mat4 earthModel = glm::mat4(1.0f);
    //position of mat4
    earthModel = glm::translate(earthModel, sunOrigin);
    //rotate around
    earthModel = glm::rotate(earthModel, (float)glfwGetTime()*glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //distance for rotation
    earthModel = glm::translate(earthModel, glm::vec3(-15.4f, 0.0f, 0.0f));

    earthModel = glm::rotate(earthModel, (float)glfwGetTime()*glm::radians(15.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    earthShader.setMat4("model", earthModel);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	earthShader.use();
	glBindVertexArray(earthVAO);
    glBindTexture(GL_TEXTURE_2D, texture.getMoonTexture());
    glm::mat4 moonModel = glm::mat4(1.0f);
    //rotate around this point
    moonModel = glm::translate(moonModel, sunOrigin);
    moonModel = glm::rotate(moonModel, (float)glfwGetTime()*glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //distance for rotation from sun
    moonModel = glm::translate(moonModel, glm::vec3(-16.4f, 0.0f, 0.0f));
    //distance for rotation from earth
    moonModel = glm::rotate(moonModel, (float)glfwGetTime()*glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    moonModel = glm::translate(moonModel, glm::vec3(-2.5f, 0.0f, 0.0f));
    moonModel = glm::scale(moonModel, glm::vec3(0.5f));
    earthShader.setMat4("model", moonModel);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	sunShader.use();
    glBindVertexArray(sunVAO);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture.getSunTexture());
    sunShader.setVec3("sunColor", glm::vec3(1.0f));
    glm::mat4 sunModel = glm::mat4(1.0f);
    sunModel = glm::translate(sunModel, sunOrigin);
    sunModel = glm::rotate(sunModel, (float)glfwGetTime()*glm::radians(15.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    sunModel = glm::scale(sunModel, glm::vec3(5.0f));
    sunShader.setMat4("model", sunModel);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

}

void VertexInput::deleteVertexAndBuffers(){
	glDeleteVertexArrays(1, &earthVAO);
	glDeleteVertexArrays(1, &sunVAO);
	glDeleteBuffers(1, &earthVBO);
	glDeleteBuffers(1, &sunVBO);
}

VertexInput::~VertexInput() {

}

