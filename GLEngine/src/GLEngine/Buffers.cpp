#include<GLEngine/Buffers.h>
#include<GLEngine/Renderer.h>
#include<GLEngine/Debugging.h>
#include<GLEngine/OpenGL/OpenGLBuffers.h>

namespace GLengine {
	
	VertexBuffer* VertexBuffer::CreateBuffer(float* vertices, unsigned int size, bool isStatic) {
		switch (RenderSettings::GetRenderAPI()) {
		case RendererAPI::API::None:
				Log("None Render API currently not supported");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, size, isStatic);
		}
	}

	void VertexBuffer::DeleteBuffer(VertexBuffer* vBuffer) {
		switch (RenderSettings::GetRenderAPI()) {
		case RendererAPI::API::None:
			break;

		case RendererAPI::API::OpenGL:
			delete (OpenGLVertexBuffer*)vBuffer;
			break;
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

	void IndexBuffer::DeleteBuffer(IndexBuffer* iBuffer) {
		switch (RenderSettings::GetRenderAPI()) {
		case RendererAPI::API::None:
			break;

		case RendererAPI::API::OpenGL:
			delete (OpenGLIndexBuffer*)iBuffer;
			break;
		}
	}

}