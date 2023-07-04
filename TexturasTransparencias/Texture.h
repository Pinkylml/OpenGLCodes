#include <GL/freeglut.h>
#include <cstdio>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture {
private:
	GLuint id;
	int width, height, nrChannels;
public:
	GLuint texture;
	Texture(const char* texturePath, GLint textureFormat) {
		if (id) {
			glDeleteTextures(1, &id);
		}
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
		checkData(data, textureFormat, width, height);
		stbi_image_free(data);
	}
	~Texture() { glDeleteTextures(1, &id); }

	GLuint getID() const { return id; }

	void bind(GLenum type) {
		glEnable(type);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(type, id);
	}

	void unbind(GLenum type) {
		glDisable(type);
		glBindTexture(type, 0);
	}

private:
	void checkData(unsigned char* data, GLint format, int width, int height) {
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		}
		else {
			printf("Error al cargar la imagen");
		}
	}
};