#pragma once
#include <GLEngine/Shader.h>

namespace GLengine {
	class OpenGLShader : public Shader {
	private:
		unsigned int shaderProgram;
		bool CompileShader(GLenum shaderType, unsigned int& shaderRef, const char* shaderSource);
		bool CompileVertexShader(std::string& shaderSource, unsigned int& shaderRef);
		bool CompileFragmentShader(std::string& shaderSource, unsigned int& shaderRef);
		bool LinkShaderProgram(unsigned int& vertShader, unsigned int& fragShader);
	public:
		OpenGLShader(std::string source);
		~OpenGLShader();
		void CompileShaders(std::string source);
		void UseShader();
		void Unbind();
		void SetBool(const char* attribName, bool value);
		void SetInt(const char* attribName, int value);
		void SetFloat(const char* attribName, float value);
		void SetMatrix4f(const char* attribName, float* value);
		void SetUniform4f(const char* attribName, glm::vec4 value);
	};
}