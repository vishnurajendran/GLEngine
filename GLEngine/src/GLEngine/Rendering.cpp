#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <string>
#include <iostream>
#include <glad/glad.h>

#include "GLEngine/Debugging.h"
#include "GLEngine/Rendering.h"
#include "GLEngine/FileHandling.h"
#include "GLEngine/HelperDefinitions.h"

namespace GLengine {
#pragma region Shader Methods

	Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
		char* vShaderSource = ReadTextFile(vertexShaderPath);
		char* fShaderSource = ReadTextFile(fragmentShaderPath);
		CompileShaders(vShaderSource, fShaderSource);
	}

	void Shader::CompileShaders(const char* vShaderSource, const char* fShaderSource) {

		unsigned int vertexShader;
		unsigned int fragmentShader;

		int compilationSuccess;
		int linkingSuccess;
		char log[512];

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderSource, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compilationSuccess);

		if (!compilationSuccess) {
			glGetShaderInfoLog(vertexShader, 512, NULL, log);
			LogError("VERTEX SHADER COMPILATION FAILED");
			LogError((std::string("[") + std::string(vShaderSource) + std::string("]")).c_str());
			LogError(log);
			return;
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compilationSuccess);

		if (!compilationSuccess) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, log);
			LogError("FRAGMENT SHADER COMPILATION FAILED");
			LogError((std::string("[") + std::string(fShaderSource) + std::string("]")).c_str());
			LogError(log);
			return;
		}

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkingSuccess);
		if (!linkingSuccess) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, log);
			LogError("SHADER LINKING FAILED");
			LogError(log);
			return;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	Shader::~Shader() {
		glDeleteProgram(shaderProgram);
	}

	void Shader::UseShader() {
		glUseProgram(shaderProgram);
	}

	void Shader::SetBool(const char* attribName, bool value) {
		glUniform1i(glGetUniformLocation(shaderProgram, attribName), (int)value);
	}

	void Shader::SetInt(const char* attribName, int value) {
		glUniform1i(glGetUniformLocation(shaderProgram, attribName), value);
	}

	void Shader::SetFloat(const char* attribName, float value) {
		glUniform1f(glGetUniformLocation(shaderProgram, attribName), value);
	}

	void Shader::SetMatrix4f(const char* attribName, float* matrixPtr) {
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, attribName);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, matrixPtr);
	}

#pragma endregion

#pragma region Texture2D Methods
	Texture2D::~Texture2D() {
		glDeleteTextures(1, &texture);
	}

	Texture2D::Texture2D(const char* imgPath, int reqComp, TextureFormat format, TextureWrap wrap, int texOrder)
	{
		this->order = texOrder;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(imgPath, &width, &height, &noOfColorChannels, reqComp);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (data) {

			glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			LogError((std::string("Failed to load Texture at path ") + std::string(imgPath)).c_str());
		}
		stbi_image_free(data);
	}

	void Texture2D::Bind() {
		glActiveTexture(GL_TEXTURE0 + order);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

#pragma endregion

#pragma region Material Methods
	Material::Material(Shader* shaderToUse, Texture2D texturesToUse[], int texArraySize)
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
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	Shape2D::Shape2D(float* vertices, int vertexArraySize, unsigned int* indices, int indexArraySize, Material* material) {
		this->vertices = vertices;
		this->indices = indices;
		this->vertexArrayLen = vertexArraySize;
		this->indexArrayLen = indexArraySize;
		this->material = material;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertexArrayLen, this->vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->indexArrayLen, this->indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	void Shape2D::PrepareToDraw() {
		material->Use();
	}

	void Shape2D::Draw() {

		//bind the vertices and indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBindVertexArray(VAO);

		//draw the points
		glDrawElements(GL_TRIANGLES, indexArrayLen, GL_UNSIGNED_INT, 0);

		//unbind the vertices

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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

