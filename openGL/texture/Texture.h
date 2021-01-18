#ifndef TEXTURE_H_
#define TEXTURE_H_
#include "../shader/Shader.hpp"

#include <glm/glm.hpp>

class Texture {
	public:
		Texture();
		virtual ~Texture();
		void loadTexture();
		unsigned int getEarthTexture();
		unsigned int getSunTexture();
		unsigned int getMoonTexture();
		unsigned char* earthData;
		unsigned char* sunData;
		unsigned char* moonData;

		void transformTexture(Shader earthShader, Shader sunShader);

	private:
		unsigned int earthTexture;
		unsigned int sunTexture;
		unsigned int moonTexture;
};

#endif /* TEXTURE_H_ */
