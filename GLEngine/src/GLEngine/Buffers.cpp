#include<GLEngine/Buffers.h>
#include<GLEngine/Renderer.h>
#include<GLEngine/Debugging.h>
#include<GLEngine/OpenGL/OpenGLBuffers.h>

namespace GLengine {
	
	VertexBuffer* VertexBuffer::CreateBuffer(float* vertices, unsigned int size) {
		switch (RenderSettings::GetRenderAPI()) {
		case RendererAPI::API::None:
				Log("None Render API currently not supported");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}
	}

	IndexBuffer* IndexBuffer::CreateBuffer(unsigned int* indices, unsigned int size) {
		switch (RenderSettings::GetRenderAPI()) {
			case RendererAPI::API::None:
				Log("None Render API currently not supported");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return new OpenGLIndexBuffer(indices, size);
		}
	}

}