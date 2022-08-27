#include <GLEngine/Renderer.h>
#include <GLEngine/OpenGL/OpenGLVertexArray.h> 

namespace GLengine {
	VertexArray* VertexArray::Create() {
		switch (RenderSettings::GetRenderAPI()) {
			case RendererAPI::API::None:   return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
	}

	void VertexArray::Delete(VertexArray* vArray) {
		switch (RenderSettings::GetRenderAPI()) {
		case RendererAPI::API::None:
			break;
		case RendererAPI::API::OpenGL:
			delete (OpenGLVertexArray*)vArray;
			break;
		}
	}
}
