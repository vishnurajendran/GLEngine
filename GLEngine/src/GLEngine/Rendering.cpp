
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
#pragma region Material Methods
	Material::Material(Shader* shaderToUse, Texture2D* texturesToUse, int texArraySize)
	{
		shader = shaderToUse;
		textures = texturesToUse;
		lenOfTex = texArraySize;
	}

	void Material::Use() {
		for (int i = 0; i < lenOfTex; i++) {
			textures[i].Bind();
		}
		shader->UseShader();
	}

	void Material::SetInt(const char* attrib, int value) { shader->UseShader(); shader->SetInt(attrib, value); }
	void Material::SetFloat(const char* attrib, float value) { shader->UseShader(); shader->SetFloat(attrib, value); }
	void Material::SetBool(const char* attrib, bool value) { shader->UseShader(); shader->SetBool(attrib, value); }
	void Material::SetMatrix4f(const char* attrib, float* valuePtr) { shader->UseShader(); shader->SetMatrix4f(attrib, valuePtr); }

#pragma endregion

#pragma region Shape2D Methods

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

	void Shape2D::PrepareToDraw() {
		material->Use();
	}

	void Shape2D::Draw() {
		vArray->Bind();
		//draw the points
		Renderer::Submit(vArray);
		//unbind
		vArray->Unbind();
	}

	void Shape2D::SetModelMatrix(glm::mat4 modelMatrix) {
		material->SetMatrix4f("model", glm::value_ptr(modelMatrix));
	}

	void Shape2D::SetViewMatrix(glm::mat4 viewMatrix) {
		material->SetMatrix4f("view", glm::value_ptr(viewMatrix));
	}

	void Shape2D::SetProjectionMatrix(glm::mat4 projectionMatrix) {
		material->SetMatrix4f("projection", glm::value_ptr(projectionMatrix));
	}
#pragma endregion
}

