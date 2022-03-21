#include <GLEngine/OpenGL/OpenGLTexture2D.h>
#include <GLEngine/Renderer.h>
#include <GLEngine/Texture2D.h>
#include <GLEngine/Debugging.h>

namespace GLengine {
	
	Texture2D* Texture2D::CreateTexture(const char* imgPath, int reqComp, TextureFormat format, TextureWrap wrap, int texOrder) {

		switch (RenderSettings::GetRenderAPI()) {
		case RendererAPI::API::OpenGL:
			return new OpenGLTexture2D(imgPath, reqComp, format, wrap, texOrder);
		case RendererAPI::API::None:
			LogError("None API Type not supported");
			return nullptr;
		}

	}

	void Texture2D::Bind() {

	}
}