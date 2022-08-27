#pragma once
#include <GLEngine/Texture2D.h>
namespace GLengine {
	typedef unsigned char Byte;
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const char* imgPath, int reqComp, TextureFormat format, TextureWrap wrap, int texOrder);
		OpenGLTexture2D(unsigned char* data, int width, int height, TextureFormat format, TextureWrap wrap, int texOrder);
		~OpenGLTexture2D();
		void Bind();
		void SetTexturePixels(unsigned char* data, int offestX,int offsetY, int width, int height);
		int SaveTexture(std::string fileName);

		inline static void SetPackingAlignment(int packing) {
			glPixelStorei(GL_UNPACK_ALIGNMENT, packing);
		}
	};

}