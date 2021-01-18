#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../shader/Shader.hpp"

class Light {

	public:
	Light(unsigned int VAO);
	virtual ~Light();

};

#endif /* LIGHT_HPP_ */
