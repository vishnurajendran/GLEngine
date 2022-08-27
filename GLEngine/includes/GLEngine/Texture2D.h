#pragma once
#include <GLEngine/Core/Core.h>
#include <string>
#include <glad/glad.h>

namespace GLengine {
	enum GLENGINE_API TextureWrap {
		Repeat=0,
		RepeatMirrored,
		EdgeClamp,
		BorderClamp
	};

	enum GLENGINE_API TextureFormat {
		ALPHA=0,
		RED,
		BLUE,
		GREEN,
		RGB,
		RGBA,
	};

	class GLENGINE_API Texture2D {
	protected:
		int order = 0;
		int width;
		int height;
		int noOfColorChannels;
		TextureFormat format;
		TextureWrap wrap;
		unsigned int texture;
	public:
		static Texture2D* CreateTexture(const char* imgPath, int reqComp, TextureFormat format, TextureWrap wrap, int texOrder = 0);
		static Texture2D* CreateTexture(unsigned char* data, int width, int height, TextureFormat format, TextureWrap wrap, int texOrder = 0);
		static Texture2D* CreateEmptyTexture(int width, int height, TextureFormat format, TextureWrap, int texOrder = 0);
		static void SetPackingAlignment(int packing);
		virtual int SaveTexture(std::string fileName) = 0;
		virtual void SetTexturePixels(unsigned char* data, int offsetX,int offsetY, int width, int height) = 0;
		virtual void Bind()=0;
	};
}