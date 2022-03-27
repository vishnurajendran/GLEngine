
#include <string>
#include <iostream>
#include <glad/glad.h>
#include "GLEngine/Debugging.h"
#include "GLEngine/Rendering.h"
#include "GLEngine/FileHandling.h"
#include "GLEngine/HelperDefinitions.h"
#include "GLEngine/Buffers.h"
#include "GLEngine/Renderer.h"

namespace GLengine {

	Shape2D::~Shape2D() {
		vArray->~VertexArray();
	}

	Shape2D::Shape2D(float* vertices, int vertexArraySize, unsigned int* indices, int indexArraySize, Material* material) {
		this->material = material;

		vArray = VertexArray::Create();
		VertexBuffer* vBuffer = VertexBuffer::CreateBuffer(vertices, vertexArraySize);
		IndexBuffer* iBuffer = IndexBuffer::CreateBuffer(indices, indexArraySize);

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position", false},
			{ ShaderDataType::Float3, "a_Color", false},
			{ ShaderDataType::Float2, "a_TexCoord", false}
		};

		vBuffer->SetLayout(layout);
		vArray->AddVertexBuffer(vBuffer);
		vArray->SetIndexBuffer(iBuffer);
	}

	void Shape2D::Draw() {
		//draw the points
		Renderer::Submit(RenderLayer::World, new RenderRequest("Shape2D",vArray, material,RendererAPI::RenderPrimitive::TRIANGLES, 0));
	}

	void Shape2D::SetModelMatrix(glm::mat4 modelMatrix) {
		material->SetMatrix4f("model", modelMatrix);
	}

	void Shape2D::SetViewMatrix(glm::mat4 viewMatrix) {
		material->SetMatrix4f("view", viewMatrix);
	}

	void Shape2D::SetProjectionMatrix(glm::mat4 projectionMatrix) {
		material->SetMatrix4f("projection", projectionMatrix);
	}
}

