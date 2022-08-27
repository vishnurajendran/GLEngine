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
	//std::map<std::string, FontFamily*> ResourceManager::fonts;

	int ResourceManager::autoTexKeyId = 0;
	int ResourceManager::autoShaderKeyId = 0;
	int ResourceManager::autoMatKeyId = 0;

	const std::string PATH_TO_AUDIO = "Assets/Audio";

#pragma region Create Methods
	
	std::string ResourceManager::CreateTexture2D(std::string path, int reqComp, TextureFormat texFormat, TextureWrap wrap, int texOrder) {
		std::string autoName = "Tex_" + std::to_string(autoTexKeyId++);
		CreateTexture2D(autoName, path, reqComp, texFormat, wrap, texOrder);
		return autoName;
	}
	
	void ResourceManager::CreateTexture2D(std::string name, std::string path, int reqComp, TextureFormat texFormat, TextureWrap wrap, int texOrder) {

		if (textures.find(name) != textures.end()) {
			return;
		}

		textures.insert({ name, Texture2D::CreateTexture(path.c_str(), reqComp, texFormat, wrap, texOrder) });
		textureKeys.push_back(name);
	}


	std::string ResourceManager::CreateTexture2D(unsigned char* data, int width, int height, TextureFormat texFormat, TextureWrap wrap, int texOrder) {
		std::string autoName = "Tex_" + std::to_string(autoTexKeyId++);
		CreateTexture2D(autoName, data, width, height, texFormat, wrap, texOrder);
		return autoName;
	}

	void ResourceManager::CreateTexture2D(std::string name,unsigned char* data, int width, int height, TextureFormat texFormat, TextureWrap wrap, int texOrder) {

		if (textures.find(name) != textures.end()) {
			return;
		}

		textures.insert({ name, Texture2D::CreateTexture(data, width, height, texFormat, wrap, texOrder) });
		textureKeys.push_back(name);
	}

	void ResourceManager::CreateEmptyTexture2D(std::string name, int width, int height, TextureFormat texFormat, TextureWrap wrap, int texOrder) {

		if (textures.find(name) != textures.end()) {
			return;
		}

		textures.insert({ name, Texture2D::CreateEmptyTexture(width, height, texFormat, wrap, texOrder) });
		textureKeys.push_back(name);
	
	}

	std::string ResourceManager::CreateEmptyTexture2D( int width, int height, TextureFormat texFormat, TextureWrap wrap, int texOrder) {
		std::string autoName = "Tex_" + std::to_string(autoTexKeyId++);
		CreateEmptyTexture2D(autoName, width, height, texFormat, wrap, texOrder);
		return autoName;
	}

	void ResourceManager::CreateShader(std::string name, std::string shaderPath) {

		if (shaders.find(name) != shaders.end()) {
			return;
		}

		shaders.insert({ name, Shader::CreateShader(ReadTextFile(shaderPath.c_str()))});
		shaderKeys.push_back(name);
	}

	std::string ResourceManager::CreateShader(std::string shaderPath) {
		std::string autoName = "Shader_" + std::to_string(autoShaderKeyId++);
		CreateShader(autoName, shaderPath);
		return autoName;
	}


	void ResourceManager::CreateMaterial(std::string name, Shader* shader, Texture2D* textures, int lenOfTex) {

		if (materials.find(name) != materials.end()) {
			return;
		}

		materials.insert({ name, new Material(shader,textures, lenOfTex) });
		materialKeys.push_back(name);
	}

	std::string ResourceManager::CreateMaterial(Shader* shader, Texture2D* textures, int lenOfTex) {
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

	/*FontFamily* ResourceManager::GetFontFamily(std::string fontName) {
		if (fonts.find(fontName) != fonts.end()) {
			return fonts.at(fontName);
		}
		else {
			FontFamily* font = new FontFamily(fontName);
			fonts.insert({ fontName, font });
			return font;
		}
	}*/

	AudioClip* ResourceManager::LoadClip(std::string clipName) {
		std::string path = PATH_TO_AUDIO + "/" + clipName;
		if (!DirExists(PATH_TO_AUDIO.c_str())) {
			MakeDirectory(PATH_TO_AUDIO.c_str());
		}
		if (!FileExists(path.c_str())) {
			auto err = "ResourceManager::Clip " + clipName + " could not be found at path " + path;
			Debug::LogError(err.c_str());
			return nullptr;
		}
		return AudioSystem::GetClip(path);
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

		LogInfo("[ Resource Manager ] Cleaned All Resources Cache");
	}

#pragma endregion
}