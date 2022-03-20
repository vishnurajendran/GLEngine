#pragma once
#include <GLEngine/Shader.h>

namespace GLengine {
	class OpenGLShader : public Shader {
	private:
		unsigned int shaderProgram;
	public:
		OpenGLShader(std::string source);
		~OpenGLShader();
		void CompileShaders(std::string source);
		void UseShader();
		void SetBool(const char* attribName, bool value);
		void SetInt(const char* attribName, int value);
		void SetFloat(const char* attribName, float value);
		void SetMatrix4f(const char* attribName, float* value);
		void SetUniform4f(const char* attribName, glm::vec4 value);
	};
}