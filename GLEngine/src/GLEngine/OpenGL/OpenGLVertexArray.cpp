#include <glad/glad.h>
#include <GLEngine/OpenGL/OpenGLVertexArray.h>
#include <GLEngine/OpenGL/OpenGLHelper.h>

namespace GLengine {

	OpenGLVertexArray::OpenGLVertexArray() {
		glGenVertexArrays(1, &arrayId);
		Bind();
	}

	void OpenGLVertexArray::AddVertexBuffer(VertexBuffer* vBuffer) {
		Bind();
		vBuffer->Bind();
		unsigned int index = 0;
		BufferLayout layout = vBuffer->GetLayout();
		for (auto element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,ShaderDataTypeToOpendGLSize(element.Type),
					ShaderDataTypeToGLEnum(element.Type),(element.Normalised?GL_TRUE: GL_FALSE),
					layout.Stride(), (void*)element.Offset);

			index++;
		}

		vBuffers.push_back(vBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* iBuffer) {
		Bind();
		iBuffer->Bind();
		this->iBuffer = iBuffer;
	}

	void OpenGLVertexArray::Bind() {
		glBindVertexArray(arrayId);
	}

	void OpenGLVertexArray::Unbind() {
		glBindVertexArray(0);
	}
}