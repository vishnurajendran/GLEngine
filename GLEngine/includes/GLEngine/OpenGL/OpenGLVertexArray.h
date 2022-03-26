#pragma once
#include<GLEngine/VertexArray.h>
namespace GLengine {
	class OpenGLVertexArray : public VertexArray {
		unsigned int arrayId;
		std::vector<VertexBuffer*>* vBuffers;
		IndexBuffer* iBuffer;
	public:
		OpenGLVertexArray();
		void AddVertexBuffer(VertexBuffer* vBuffer) override;
		void SetIndexBuffer(IndexBuffer* iBuffer) override;
		void Bind() override;
		void Unbind() override;
		inline IndexBuffer* GetIndexBuffer() override { return iBuffer; }
		inline std::vector<VertexBuffer*> GetVertexBuffers() override { return *vBuffers; }
	};
}