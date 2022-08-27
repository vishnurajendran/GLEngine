#include <GLEngine/Material.h>
#include <GLEngine/Shader.h>
#include <GLEngine/Debugging.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <map>

namespace GLengine {

	Material::~Material() {
		Cleanup();
		shader = nullptr;
		textures = nullptr;
	}

	Material::Material(Shader* shaderToUse, Texture2D* texturesToUse, int texArraySize=0)
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
		ApplyShaderAttribs();
	}

	void Material::Cleanup() {
		intAttribMap.clear();
		floatAttribMap.clear();
		boolAttribMap.clear();
		mat4AttribMap.clear();
		uniform4AttribMap.clear();
	}


	void Material::CacheIntAttrib(std::string name, int value) {
		intAttribMap.insert({ name, value });
	}
	void Material::CacheFloatAttrib(std::string name, float value) {
		floatAttribMap.insert({ name, value });
	}
	void Material::CacheBoolAttrib(std::string name, bool value) {
		boolAttribMap.insert({ name, value });
	}
	void Material::CacheMatrix4fAttrib(std::string name, glm::mat4 value) {
		mat4AttribMap.insert({ name, value });
	}
	void Material::CacheUniform4fAttrib(std::string name, glm::vec4 value) {
		uniform4AttribMap.insert({ name, value });
	}

	void Material::ApplyShaderAttribs() {
		
		shader->UseShader();
		for (auto attrib : intAttribMap) {
			shader->SetInt(attrib.first.c_str(), attrib.second);
		}

		for (auto attrib : floatAttribMap) {
			shader->SetFloat(attrib.first.c_str(), attrib.second);
		}

		for (auto attrib : boolAttribMap) {
			shader->SetBool(attrib.first.c_str(), attrib.second);
		}

		for (auto attrib : mat4AttribMap) {
			shader->SetMatrix4f(attrib.first.c_str(), glm::value_ptr(attrib.second));
		}

		for (auto attrib : uniform4AttribMap) {
			shader->SetUniform4f(attrib.first.c_str(), attrib.second);
		}

	}

	void Material::SetInt(const char* attrib, int value) {
		CacheIntAttrib(attrib, value); 
	}
	void Material::SetFloat(const char* attrib, float value) { 
		CacheFloatAttrib(attrib, value);
	}
	void Material::SetBool(const char* attrib, bool value) { 
		CacheBoolAttrib(attrib, value);
	}
	void Material::SetMatrix4f(const char* attrib, glm::mat4 value) { 
		CacheMatrix4fAttrib(attrib, value);
	}
	void Material::SetUniform4f(const char* attrib, glm::vec4 value) { 
		CacheUniform4fAttrib(attrib, value);
	}
}