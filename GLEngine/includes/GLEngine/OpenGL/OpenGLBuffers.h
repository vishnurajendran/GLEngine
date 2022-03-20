#pragma once
#include<GLEngine/Buffers.h>

namespace GLengine {
	class OpenGLVertexBuffer : public VertexBuffer {
		unsigned int bufferId;
		unsigned int layoutId;
	public:
		~OpenGLVertexBuffer();
		OpenGLVertexBuffer(float* vertices, unsigned int count);
		void SetLayout(BufferLayout& layout) override;
		BufferLayout& GetLayout() override;
		void Bind() override;
		void Unbind() override;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
		unsigned int bufferId;
	public:
		~OpenGLIndexBuffer();
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		void Bind() override;
		void Unbind() override;
	};
}