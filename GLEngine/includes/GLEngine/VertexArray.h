#pragma once
#include <GLEngine/Buffers.h>

namespace GLengine {
	class VertexArray
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void AddVertexBuffer(VertexBuffer* vBuffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* iBuffer) = 0;
		virtual std::vector<VertexBuffer*> GetVertexBuffers() = 0;
		virtual IndexBuffer* GetIndexBuffer() = 0;
		static VertexArray* Create();
	};
}

