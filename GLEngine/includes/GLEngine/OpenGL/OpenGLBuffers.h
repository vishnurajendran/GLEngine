#pragma once
#include<GLEngine/Buffers.h>

namespace GLengine {
	class OpenGLVertexBuffer : public VertexBuffer {
		float* vertMemory;
		unsigned int bufferId=0;
		unsigned int layoutId=0;
	public:
		~OpenGLVertexBuffer();
		OpenGLVertexBuffer(float* vertices, unsigned int count, bool isStatic=true);
		void SetLayout(BufferLayout& layout) override;
		BufferLayout& GetLayout() override;
		void Bind() override;
		void Unbind() override;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
		unsigned int bufferId;
		unsigned int* indexMemory;
	public:
		~OpenGLIndexBuffer();
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		void Bind() override;
		void Unbind() override;
	};
}