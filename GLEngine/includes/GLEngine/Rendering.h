#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "GLEngine/Debugging.h"
#include "Core/Core.h"
#include<string>

namespace GLengine {
	enum GLENGINE_API TextureWrap {
		Repeat = GL_REPEAT,
		RepeatMirrored = GL_MIRRORED_REPEAT,
		EdgeClamp = GL_CLAMP_TO_EDGE,
		BorderClamp = GL_CLAMP_TO_BORDER
	};

	enum GLENGINE_API TextureFormat {
		RGB = GL_RGB,
		RGBA = GL_RGBA,
	};

	class Shader {
	private:
		unsigned int shaderProgram;
		void CompileShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
	public:
		Shader(const char* vShaderSource, const char* fShaderSource);
		~Shader();
		void UseShader();
		void SetBool(const char* attribName, bool value);
		void SetInt(const char* attribName, int value);
		void SetFloat(const char* attribName, float value);
		void SetMatrix4f(const char* attribName, float* value);
	};

	class GLENGINE_API Texture2D {
		int order = 0;
		int width;
		int height;
		int noOfColorChannels;
		unsigned int texture;
	public:
		~Texture2D();
		Texture2D(const char* imgPath, int reqComp, TextureFormat format, TextureWrap wrap, int texOrder = 0);
		void Bind();
	};

	class GLENGINE_API Material {
		Shader* shader;
		Texture2D* textures;
		int lenOfTex;

	public:
		~Material() { }
		Material(Shader* shader, Texture2D textures[], int lenOfTex = 0);
		void Use();
		void SetInt(const char* attrib, int value);
		void SetFloat(const char* attrib, float value);
		void SetBool(const char* attrib, bool value);
		void SetMatrix4f(const char* attrib, float* valuePtr);
	};

	class GLENGINE_API Shape2D {
	private:
		float* vertices;
		unsigned int vertexArrayLen;
		unsigned int* indices;
		unsigned int indexArrayLen;
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;
		Material* material;

	public:
		~Shape2D();
		Shape2D() = default;
		Shape2D(float* vertices, int vertexArraySize, unsigned int* indices, int indexArraySize, Material* material);
		void PrepareToDraw();
		void Draw();
		void SetModelMatrix(glm::mat4 modelMatrix);
		void SetViewMatrix(glm::mat4 viewMatrix);
		void SetProjectionMatrix(glm::mat4 projectionMatrix);
	};
}

