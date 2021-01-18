
#include "../glad/glad.h"
#include "Texture.h"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include "../shader/Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Texture::Texture() {

}

void Texture::loadTexture(){

	    glGenTextures(1, &earthTexture);
	    glBindTexture(GL_TEXTURE_2D, earthTexture);
	     // set the texture wrapping parameters
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	    // set texture filtering parameters
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    // load image, create texture and generate mipmaps
	    int width, height, nrChannels;
	    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	    earthData = stbi_load("./texture/earth.jpg", &width, &height, &nrChannels, 0);
	    if (earthData)
	    {
	        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, earthData);
	       // glGenerateMipmap(GL_TEXTURE_2D);
	    }
	    else
	    {
	        std::cout << "Failed to load texture" << std::endl;
	    }

	    stbi_image_free(earthData);

	    glGenTextures(1, &sunTexture);
	    glBindTexture(GL_TEXTURE_2D, sunTexture);
	     // set the texture wrapping parameters
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	    // set texture filtering parameters
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    // load image, create texture and generate mipmaps

	    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	    sunData = stbi_load("./texture/sun.jpg", &width, &height, &nrChannels, 0);
	    if (sunData)
	    {
	        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, sunData);
	       // glGenerateMipmap(GL_TEXTURE_2D);
	    }
	    else
	    {
	        std::cout << "Failed to load texture" << std::endl;
	    }

	    stbi_image_free(sunData);

	    glGenTextures(1, &moonTexture);
	    glBindTexture(GL_TEXTURE_2D, moonTexture);
	     // set the texture wrapping parameters
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	    // set texture filtering parameters
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    // load image, create texture and generate mipmaps

	    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	    moonData = stbi_load("./texture/moon.jpeg", &width, &height, &nrChannels, 0);
	    if (moonData)
	    {
	        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, moonData);
	       // glGenerateMipmap(GL_TEXTURE_2D);
	    }
	    else
	    {
	        std::cout << "Failed to load texture" << std::endl;
	    }

	    stbi_image_free(moonData);


}

void Texture::transformTexture(Shader earthShader, Shader sunShader){
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)800/(float)600, 0.1f, 100.0f);

	earthShader.use();
	earthShader.setMat4("projection", projection);

	sunShader.use();
	sunShader.setMat4("projection", projection);

}

unsigned int Texture::getEarthTexture(){
	return earthTexture;
}

unsigned int Texture::getMoonTexture(){
	return moonTexture;
}

unsigned int Texture::getSunTexture(){
	return sunTexture;
}

Texture::~Texture() {

}

