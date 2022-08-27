#pragma once
#include <GLEngine/Texture2D.h>
#include <GLEngine/Shader.h>
#include <map>

namespace GLengine {
	class GLENGINE_API Material {
		Shader* shader;
		Texture2D* textures;
		int lenOfTex;

		std::map<std::string, int> intAttribMap;
		std::map<std::string, float> floatAttribMap;
		std::map<std::string, bool> boolAttribMap;
		std::map<std::string, glm::mat4> mat4AttribMap;
		std::map<std::string, glm::vec4> uniform4AttribMap;

		void ApplyShaderAttribs();
		void CacheIntAttrib(std::string name, int value);
		void CacheFloatAttrib(std::string name, float value);
		void CacheBoolAttrib(std::string name, bool value);
		void CacheMatrix4fAttrib(std::string name, glm::mat4 value);
		void CacheUniform4fAttrib(std::string name, glm::vec4 value);
	public:
		~Material();
		Material(Shader* shader, Texture2D* textures, int lenOfTex);
		void Use();
		void Cleanup();
		void SetInt(const char* attrib, int value);
		void SetFloat(const char* attrib, float value);
		void SetBool(const char* attrib, bool value);
		void SetMatrix4f(const char* attrib, glm::mat4 value);
		void SetUniform4f(const char* attrib, glm::vec4 value);
	};
}