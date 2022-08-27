#pragma once
#include <map>
#include <vector>
#include <string>
#include <GLEngine/Rendering.h>
#include <GLEngine/Shader.h>
#include <GLEngine/AudioSystem/AudioSystem.h>

//#include <GLEngine/FontFamily.h>

namespace GLengine {
	class GLENGINE_API ResourceManager {

		//static dicts to store the objects during runtime;

		static int autoTexKeyId;
		static std::vector<std::string> textureKeys;
		static std::map<std::string, Texture2D*> textures;

		static int autoShaderKeyId;
		static std::vector<std::string> shaderKeys;
		static std::map<std::string, Shader*> shaders;

		static int autoMatKeyId;
		static std::vector<std::string> materialKeys;
		static std::map<std::string, Material*> materials;
		static std::map<std::string, char*> imageData;
		//static std::map<std::string, FontFamily*> fonts;

	public:
		//Create Methods

		
		static void CreateTexture2D(std::string name, std::string path, int reqComp, TextureFormat texFormat, TextureWrap wrap, int texOrder = 0);
		static std::string CreateTexture2D(std::string path, int reqComp, TextureFormat texFormat, TextureWrap wrap, int texOrder = 0);
		
		static void CreateTexture2D(std::string name,unsigned char* data, int width, int height, TextureFormat texFormat, TextureWrap wrap, int texOrder = 0);
		static std::string CreateTexture2D(unsigned char* data, int width, int height, TextureFormat texFormat, TextureWrap wrap, int texOrder = 0);
		
		static void CreateEmptyTexture2D(std::string name, int width, int height, TextureFormat texFormat, TextureWrap wrap, int texOrder);
		static std::string CreateEmptyTexture2D(int width, int height, TextureFormat texFormat, TextureWrap wrap, int texOrder = 0);

		static void CreateShader(std::string name, std::string shaderPath);
		static std::string CreateShader(std::string shaderPath);
		
		static void CreateMaterial(std::string name, Shader* shader, Texture2D* textures, int lenOfTex = 0);
		static std::string CreateMaterial(Shader* shader, Texture2D* textures, int lenOfTex = 0);
		
		static Shader* GetShader(std::string name);
		static Texture2D* GetTexture2D(std::string name);
		static Material* GetMaterial(std::string name);
		
		//static FontFamily* GetFontFamily(std::string fontName);


		static AudioClip* LoadClip(std::string clipName);

		static void CleanShader(std::string name);
		static void CleanTexture2D(std::string name);
		static void CleanMaterial(std::string name);
		static void CleanAll();
	};
}

