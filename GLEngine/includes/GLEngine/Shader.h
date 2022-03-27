#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>
#include "GLEngine/Debugging.h"
namespace GLengine {
	
	enum ShaderType {
		Unknown=0,
		Vertex,
		Fragment
	};

	class Shader {
	protected:
		std::string GetTokenFromShaderType(ShaderType type);
		int GetPositionOfSource(ShaderType type, std::string shaderSource);
		int GetPositionOfSource(std::string token, std::string shaderSource);
		const char* ExtractShaderSource(ShaderType type, std::string shaderSource);

	public:
		static Shader* CreateShader(std::string shaderSource);
		virtual void CompileShaders(std::string source)=0;
		virtual void UseShader() = 0;
		virtual void Unbind() = 0;
		virtual void SetBool(const char* attribName, bool value) = 0;
		virtual void SetInt(const char* attribName, int value) = 0;
		virtual void SetFloat(const char* attribName, float value) = 0;
		virtual void SetMatrix4f(const char* attribName, float* value) = 0;
		virtual void SetUniform4f(const char* attribName, glm::vec4 value) =0;
	};

}