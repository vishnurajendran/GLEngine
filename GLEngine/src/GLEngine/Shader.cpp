#include <GLEngine/Shader.h>
#include <GLEngine/OpenGL/OpenGLShader.h>
#include <GLEngine/Renderer.h>
namespace GLengine {
	
	Shader* Shader::CreateShader(std::string shaderSource) {
		switch (RenderSettings::GetRenderAPI())
		{
			case RendererAPI::API::OpenGL:
				return new OpenGLShader(shaderSource);
			case RendererAPI::API::None:
				LogError("Illegal API type, Shader not created");
				return nullptr;
		}
	}

	std::string Shader::GetTokenFromShaderType(ShaderType type) {
		switch (type) {
		case ShaderType::Vertex: return "#shadertype vertex";
		case ShaderType::Fragment: return "#shadertype fragment";
		case ShaderType::Unknown: LogError("Unknown shader type"); return "";
		}
	}

	int Shader::GetPositionOfSource(ShaderType type, std::string shaderSource) {
		std::string token = GetTokenFromShaderType(type);
		int pos = shaderSource.find(token);
		return pos;
	}

	int Shader::GetPositionOfSource(std::string token, std::string shaderSource) {
		int pos = shaderSource.find(token);
		return pos;
	}

	const char* Shader::ExtractShaderSource(ShaderType type, std::string shaderSource) {
		std::string* source = new std::string("");
		int len = GetTokenFromShaderType(type).size();
		int startPos = GetPositionOfSource(type, shaderSource);
		if (startPos >= 0) {
			startPos += len;
			*source = shaderSource.substr(startPos, shaderSource.size() - startPos);
			int endPos = GetPositionOfSource("#shadertype", *source);
			if (endPos >= 0)
				*source = source->substr(0, endPos);
		}
		return source->c_str();
	}
}