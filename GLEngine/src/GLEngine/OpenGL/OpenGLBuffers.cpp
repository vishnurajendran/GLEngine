#include <glad/glad.h>
#include <GLEngine/OpenGL/OpenGLBuffers.h>
#include <GLEngine/Debugging.h>

namespace GLengine {
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int count, bool isStatic) {
		vertMemory = vertices;
		length = count;
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, isStatic?GL_STATIC_DRAW:GL_DYNAMIC_DRAW);
	}
	
	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		Unbind();
		glDeleteBuffers(1, &bufferId);
		if (vertMemory != nullptr) {
			delete[] vertMemory;
		}
	}

	void OpenGLVertexBuffer::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	}

	void OpenGLVertexBuffer::Unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetLayout(BufferLayout& layout) {
		this->layout = &layout;
	}

	BufferLayout& OpenGLVertexBuffer::GetLayout() {
		return *layout;
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count) {
		indexMemory = indices;
		length = count;
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		LogWarning("DELETING IARRAY");
		Unbind();
		if (indexMemory != nullptr)
			delete[] indexMemory;

		glDeleteBuffers(1, &bufferId);
	}

	void OpenGLIndexBuffer::Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
	}

	void OpenGLIndexBuffer::Unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}