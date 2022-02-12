#include "GLEngine/Debugging.h"
#include "GLEngine/ResourceManager.h"
#include "GLEngine/FileHandling.h"

namespace GLengine {
	std::vector<std::string> ResourceManager::textureKeys;
	std::vector<std::string> ResourceManager::shaderKeys;
	std::vector<std::string> ResourceManager::materialKeys;

	std::map<std::string, Texture2D*> ResourceManager::textures;
	std::map<std::string, Shader*> ResourceManager::shaders;
	std::map<std::string, Material*> ResourceManager::materials;
	std::map<std::string, char*> ResourceManager::imageData;


	int ResourceManager::autoTexKeyId = 0;
	int ResourceManager::autoShaderKeyId = 0;
	int ResourceManager::autoMatKeyId = 0;

#pragma region Create Methods
	void ResourceManager::CreateTexture2D(std::string name, std::string path, int reqComp, TextureFormat texFormat, TextureWrap wrap, int texOrder) {

		if (textures.find(name) != textures.end()) {
			LogWarning((name + std::string(" exists in cache already. skipping texture generation")).c_str());
			return;
		}

		textures.insert({ name, new Texture2D(path.c_str(), reqComp, texFormat, wrap, texOrder) });
		textureKeys.push_back(name);
		Log(("Added " + name).c_str());
	}

	std::string ResourceManager::CreateTexture2D(std::string path, int reqComp, TextureFormat texFormat, TextureWrap wrap, int texOrder) {
		std::string autoName = "Tex_" + std::to_string(autoTexKeyId++);
		CreateTexture2D(autoName, path, reqComp, texFormat, wrap, texOrder);
		return autoName;
	}

	void ResourceManager::CreateShader(std::string name, std::string vertShaderPath, std::string fragShaderPath) {

		if (shaders.find(name) != shaders.end()) {
			LogWarning((name + std::string(" exists in cache already. skipping shader generation")).c_str());
			return;
		}

		shaders.insert({ name, new Shader(vertShaderPath.c_str(), fragShaderPath.c_str()) });
		shaderKeys.push_back(name);
	}

	std::string ResourceManager::CreateShader(std::string vertShaderPath, std::string fragShaderPath) {
		std::string autoName = "Shader_" + std::to_string(autoShaderKeyId++);
		CreateShader(autoName, vertShaderPath, fragShaderPath);
		return autoName;
	}


	void ResourceManager::CreateMaterial(std::string name, Shader* shader, Texture2D textures[], int lenOfTex) {

		if (materials.find(name) != materials.end()) {
			LogWarning((name + std::string(" exists in cache already. skipping material generation")).c_str());
			return;
		}

		materials.insert({ name, new Material(shader,textures, lenOfTex) });
		materialKeys.push_back(name);
	}

	std::string ResourceManager::CreateMaterial(Shader* shader, Texture2D textures[], int lenOfTex) {
		std::string autoName = "Mat_" + std::to_string(autoMatKeyId++);
		CreateMaterial(autoName, shader, textures, lenOfTex);
		return autoName;
	}

#pragma endregion

#pragma region Fetch Methods

	Shader* ResourceManager::GetShader(std::string name) {
		if (shaders.count(name)) {
			return shaders[name];
		}
		return NULL;
	}

	Texture2D* ResourceManager::GetTexture2D(std::string name) {
		if (textures.count(name)) {
			return textures[name];
		}
		return NULL;
	}

	Material* ResourceManager::GetMaterial(std::string name) {
		if (materials.count(name)) {
			return materials[name];
		}
		return NULL;
	}

#pragma endregion

#pragma region CleanMethods

	void ResourceManager::CleanShader(std::string name) {
		if (shaders.find(name) != shaders.end()) {
			shaders.erase(name);
			std::remove(shaderKeys.begin(), shaderKeys.end(), name);
		}
	}

	void ResourceManager::CleanTexture2D(std::string name) {
		if (textures.find(name) != textures.end()) {
			textures.erase(name);
			std::remove(textureKeys.begin(), textureKeys.end(), name);
		}
	}

	void ResourceManager::CleanMaterial(std::string name) {
		if (materials.find(name) != materials.end()) {
			materials.erase(name);
			std::remove(materialKeys.begin(), materialKeys.end(), name);
		}
	}

	void ResourceManager::CleanAll() {
		for (int i = 0; i < shaders.size(); i++) {
			shaders[shaderKeys[i]]->~Shader();
			free(shaders[shaderKeys[i]]);
		}
		shaders.clear();
		shaderKeys.clear();
		;
		for (int i = 0; i < textures.size(); i++) {
			textures[textureKeys[i]]->~Texture2D();
			free(textures[textureKeys[i]]);
		}
		textures.clear();
		textureKeys.clear();

		for (int i = 0; i < materials.size(); i++) {
			materials[materialKeys[i]]->~Material();
			free(materials[materialKeys[i]]);
		}
		materials.clear();
		materialKeys.clear();

		LogInfo("Cleanded All Resources Caches");
	}

#pragma endregion
}