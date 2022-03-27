#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include "GLEngine/Debugging.h"
#include <GLEngine/Core/Core.h>
#include <GLEngine/Buffers.h>
#include <GLEngine/VertexArray.h>
#include <GLEngine/Shader.h>
#include <GLEngine/Texture2D.h>
#include <GLEngine/Material.h>
#include<string>

namespace GLengine {
	class GLENGINE_API Shape2D {
	private:
		VertexArray* vArray;
		unsigned int VAO;
		Material* material;

	public:
		~Shape2D();
		Shape2D() = default;
		Shape2D(float* vertices, int vertexArraySize, unsigned int* indices, int indexArraySize, Material* material);
		void Draw();
		void SetModelMatrix(glm::mat4 modelMatrix);
		void SetViewMatrix(glm::mat4 viewMatrix);
		void SetProjectionMatrix(glm::mat4 projectionMatrix);
	};
}

