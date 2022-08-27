#include <glad/glad.h>
#include <GLEngine/Debugging.h>
#include <GLEngine/OpenGL/OpenGLVertexArray.h>
#include <GLEngine/OpenGL/OpenGLHelper.h>

namespace GLengine {

	OpenGLVertexArray::~OpenGLVertexArray() {
		
		if (vBuffers != nullptr) {
			for (auto vBuffer : *vBuffers) {
				VertexBuffer::DeleteBuffer(vBuffer);
			}

			vBuffers->clear();
			vBuffers->shrink_to_fit();
		}

		if (iBuffer != nullptr) {
			IndexBuffer::DeleteBuffer(iBuffer);
		}
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		vBuffers = nullptr;
		iBuffer = nullptr;
		glGenVertexArrays(1, &arrayId);
		Bind();
	}

	void OpenGLVertexArray::AddVertexBuffer(VertexBuffer* vBuffer) {
		
		if (vBuffers == nullptr)
			vBuffers = new std::vector<VertexBuffer*>();
		
		Bind();
		vBuffer->Bind();
		unsigned int index = 0;
		BufferLayout layout = vBuffer->GetLayout();
		for (auto element : layout) {
			//printf("INDX (%d) GLSize (%d) GLEnum (%d) Stride (%d) Offset (%d)\n",index, ShaderDataTypeToOpendGLSize(element.Type), ShaderDataTypeToGLEnum(element.Type),layout.Stride(), element.Offset);
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,ShaderDataTypeToOpendGLSize(element.Type),
					ShaderDataTypeToGLEnum(element.Type),(element.Normalised?GL_TRUE: GL_FALSE),
					layout.Stride(), (void*)element.Offset);

			index++;
		}

		vBuffers->push_back(vBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* iBuffer) {
		
		if (iBuffer == nullptr)
			return;
		
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