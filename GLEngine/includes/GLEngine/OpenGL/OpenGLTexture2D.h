#pragma once
#include <GLEngine/Texture2D.h>
namespace GLengine {

	class OpenGLTexture2D : public Texture2D {

	public:
		OpenGLTexture2D(const char* imgPath, int reqComp, TextureFormat format, TextureWrap wrap, int texOrder);
		~OpenGLTexture2D();
		void Bind();
	};

}