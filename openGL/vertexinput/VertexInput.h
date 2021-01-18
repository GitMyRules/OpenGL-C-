#ifndef VERTEXINPUT_H_
#define VERTEXINPUT_H_

#include <glm/glm.hpp>
#include "../shader/Shader.hpp"
#include <array>
#include "../camera/Camera.hpp"

class VertexInput {

	public:
		VertexInput();
		virtual ~VertexInput();
		void update(Shader earthShader, Shader sunShader, glm::vec3 cubePositions[]);
		void deleteVertexAndBuffers();
		GLuint texLoc;
	private:
		glm::vec3 sunOrigin = glm::vec3(0.0f, 0.0f, -20.0f);
		void createVertexShader();
		void shaderProgram();
		void insertVertexData();

		unsigned int VBO, earthVBO, sunVBO,VAO,earthVAO, sunVAO, EBO;
		float timeValue;
};

#endif /* VERTEXINPUT_H_ */
