#pragma once
#include <GLEngine/Core/Core.h>
#include <glad/glad.h>

namespace GLengine {
	enum GLENGINE_API TextureWrap {
		Repeat = GL_REPEAT,
		RepeatMirrored = GL_MIRRORED_REPEAT,
		EdgeClamp = GL_CLAMP_TO_EDGE,
		BorderClamp = GL_CLAMP_TO_BORDER
	};

	enum GLENGINE_API TextureFormat {
		RGB = GL_RGB,
		RGBA = GL_RGBA,
	};

	class GLENGINE_API Texture2D {
	protected:
		int order = 0;
		int width;
		int height;
		int noOfColorChannels;
		unsigned int texture;
	public:
		static Texture2D* CreateTexture(const char* imgPath, int reqComp, TextureFormat format, TextureWrap wrap, int texOrder = 0);
		virtual void Bind()=0;
	};
}