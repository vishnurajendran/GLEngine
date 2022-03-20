#include <GLEngine/Renderer.h>
#include <GLEngine/OpenGL/OpenGLVertexArray.h> 

namespace GLengine {
	VertexArray* VertexArray::Create() {
		switch (RenderSettings::GetRenderAPI()) {
			case RendererAPI::API::None:   return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
	}
}
