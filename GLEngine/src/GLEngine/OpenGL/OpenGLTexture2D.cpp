#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>
#include <GLEngine/Debugging.h>
#include <GLEngine/OpenGL/OpenGLTexture2D.h>
namespace GLengine {
	OpenGLTexture2D::OpenGLTexture2D(const char* imgPath, int reqComp, TextureFormat format, TextureWrap wrap, int texOrder) {
		this->order = texOrder;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(imgPath, &width, &height, &noOfColorChannels, reqComp);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (data) {

			glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			LogError((std::string("Failed to load Texture at path ") + std::string(imgPath)).c_str());
		}
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &texture);
	}

	void OpenGLTexture2D::Bind() {
		glActiveTexture(GL_TEXTURE0 + order);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
}