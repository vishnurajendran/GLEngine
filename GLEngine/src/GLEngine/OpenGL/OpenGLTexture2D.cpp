#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stb_image.h>
#include <glad/glad.h>
#include <GLEngine/Debugging.h>
#include <GLEngine/OpenGL/OpenGLTexture2D.h>
namespace GLengine {

	std::string DescribeError(GLenum error) {
		switch (error) {
		case GL_NO_ERROR:
			return "GL_NO_ERROR: No error has been recorded. The value of this symbolic constant is guaranteed to be 0. ";
		case GL_INVALID_ENUM:
			return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.  ";
		case GL_INVALID_VALUE:
			return "GL_INVALID_VALUE: A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.  ";
		case GL_INVALID_OPERATION:
			return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.  ";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return
				"GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete."
				"The offending command is ignored and has no other side effect than to set the error flag.";
		case GL_OUT_OF_MEMORY:
			return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded. . ";
		case GL_STACK_UNDERFLOW:
			return "GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow. ";
		case GL_STACK_OVERFLOW:
			return "GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow. ";
		default:
			return "No Description";
		}
	}

	void TryErrorCheck(std::string title) {
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			Debug::LogError((title + DescribeError(error)).c_str());
		}
	}

	GLenum GetGLTexWrap(TextureWrap wrap) {
		switch (wrap) {
		case TextureWrap::Repeat:
			return GL_REPEAT;
		case TextureWrap::RepeatMirrored:
			return GL_MIRRORED_REPEAT;
		case TextureWrap::EdgeClamp:
			return GL_CLAMP_TO_EDGE;
		case TextureWrap::BorderClamp:
			return GL_CLAMP_TO_BORDER;
		}
	}

	GLenum GetGLTexFormat(TextureFormat format) {
		switch (format) {
		case TextureFormat::ALPHA:
			return GL_ALPHA;
		case TextureFormat::RED:
			return GL_RED;
		case TextureFormat::BLUE:
			return GL_BLUE;
		case TextureFormat::GREEN:
			return GL_GREEN;
		case TextureFormat::RGB:
			return GL_RGB;
		case TextureFormat::RGBA:
			return GL_RGBA;
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(const char* imgPath, int reqComp, TextureFormat format, TextureWrap wrap, int texOrder) {
		this->order = texOrder;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(imgPath, &width, &height, &noOfColorChannels, reqComp);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetGLTexWrap(wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetGLTexWrap(wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (data) {

			glTexImage2D(GL_TEXTURE_2D, 0, GetGLTexFormat(format), this->width, this->height, 0, GetGLTexFormat(format), GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			LogError((std::string("Failed to load Texture at path ") + std::string(imgPath)).c_str());
		}
		stbi_image_free(data);
	}

	bool IsPoT(int n)
	{
		if (n == 0)
			return false;

		return (ceil(log2(n)) == floor(log2(n)));
	}

	void AssignAlignment(TextureFormat format) {
		switch (format)
		{
		case TextureFormat::ALPHA:
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			break;
		case TextureFormat::RED:
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			break;
		case TextureFormat::BLUE:
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			break;
		case TextureFormat::GREEN:
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			break;
		case TextureFormat::RGB:
			glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
			break;
		case TextureFormat::RGBA:
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			break;
		default:
			break;
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(unsigned char* data,int width, int height, TextureFormat format, TextureWrap wrap, int texOrder) {
		this->order = texOrder;
		this->width = width;
		this->height = height;
		this->format = format;
		this->wrap = wrap;

		glActiveTexture(GL_TEXTURE0 + order);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetGLTexWrap(wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetGLTexWrap(wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		AssignAlignment(format);
		
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GetGLTexFormat(format), this->width, this->height, 0, GetGLTexFormat(format), GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			data = new unsigned char[width * height];
			LogInfo(("Created empty Buffer " + std::to_string(width * height) + " Bytes").c_str());
			LogInfo("Created empty texture");
			glTexImage2D(GL_TEXTURE_2D, 0, GetGLTexFormat(format), this->width, this->height, 0, GetGLTexFormat(format), GL_UNSIGNED_BYTE, 0);
		}

		TryErrorCheck("TEX CREATE ");
		LogWarning(("TEXTURE " + std::to_string(texture)).c_str());
	}

	void PrintData(unsigned char* data, int max, int totalTexWidth) {
		LogWarning(("MAX ELEMS " + std::to_string(max) + " MAX ELEMS SUPPORTED " + std::to_string(totalTexWidth)).c_str());
		for (int i = 0; i < max; i++) {
			printf("%d,", data[i]);
		}
		printf("\n");
	}
	
	int OpenGLTexture2D::SaveTexture(std::string fileName)
	{
		int w = this->width;
		int h = this->height;
		Byte* data = new Byte[width*height];
		glGetTexImage(GL_TEXTURE_2D, 0, GetGLTexFormat(this->format), GL_UNSIGNED_BYTE, (void*)data);
		FILE* f = fopen(fileName.c_str(), "wb");
		if (!f) return -1; // ERROR!
		unsigned bytesPerRow = (w + 3) & ~3; // align to 4 bytes (requirement)
		unsigned size
			= 14 // Bitmap file header size
			+ 12 // DIB header size
			+ 256 * 3; // palette size
		unsigned gap = size;
		size = (size + 3) & ~3; // align to 4 bytes (requirement)
		gap = size - gap; // get size of gap between end of headers and raw data
		unsigned offs = size; // store offset of raw data
		size += h * bytesPerRow; // bitmap data size in file
		/* write Bitmap file header (14 bytes) */
		{ const Byte buffer[14] = {
			'B', 'M', // magic code
			size & 0xff, size >> 8 & 0xff, size >> 16 & 0xff, size >> 24 & 0xff, // size of BMP file in bytes
			0, 0, // reserved
			0, 0, // reserved
			offs & 0xff, offs >> 8 & 0xff, offs >> 16 & 0xff, offs >> 24 & 0xff // starting offset of pixel data
		};
		if (fwrite(buffer, sizeof buffer, 1, f) != 1) return -1; // ERROR!
		}
		/* write DIB header (12 bytes) */
		{ const Byte buffer[12] = {
			12, 0, 0, 0, // size of this header
			w & 0xff, w >> 8 & 0xff, // bitmap width in pixels
			h & 0xff, h >> 8 & 0xff, // bitmap height in pixels
			1, 0, // number of color planes, must be 1
			8, 0 // number of bits per pixel
		};
		if (fwrite(buffer, sizeof buffer, 1, f) != 1) return -1; // ERROR!
		}
		/* write color palette (3 * 256 bytes) */
		for (int i = 0; i < 256; ++i) { // make a gray level palette
			Byte buffer[3] = { i, i, i };
			if (fwrite(buffer, sizeof buffer, 1, f) != 1) return -1; // ERROR!   
		}
		/* write gap (to align start address of raw data with 4 */
		for (int i = 0; i < gap; ++i) {
			if (fputc(0, f) < 0) return -1; // ERROR!
		}
		/* write raw data */
		for (int y = 0; y < h; ++y) { // for all rows
			int x = 0;
			for (; x < w; ++x) { // for all columns
				if (fputc(*data++, f) < 0) return -1; // ERROR!
			}
			// write row padding
			for (; x < bytesPerRow; ++x) {
				if (fputc(0, f) < 0) return -1; // ERROR!
			}
		}
		/* done */
		return 0;
	}

	void OpenGLTexture2D::SetTexturePixels(unsigned char* data, int offsetX,int offsetY, int width, int height) {
		glTexSubImage2D(GL_TEXTURE_2D, 0,offsetX,offsetY,width, height, GetGLTexFormat(format), GL_UNSIGNED_BYTE, data);
		TryErrorCheck("TEX PIXEL SET ");
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &texture);
	}

	void OpenGLTexture2D::Bind() {
		glActiveTexture(GL_TEXTURE0 + order);
		glBindTexture(GL_TEXTURE_2D, texture);
		TryErrorCheck("TEX BIND ");
	}
}