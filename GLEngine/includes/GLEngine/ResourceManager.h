#pragma once
#include <map>
#include <vector>
#include <string>
#include <GLEngine/Rendering.h>
#include <GLEngine/Shader.h>
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

	public:
		//Create Methods

		/// <summary>
		/// This Method Creates a Texture2D using the parameters provided and saved in runtime
		/// cache to re - use by using the name specified
		/// </summary>
		/// <param name="name"> key used to store in cache </param>
		/// <param name="path"> path to image for texture </param>
		/// <param name="reqComp"> required compression, if unsure set to 0</param>
		/// <param name="texFormat"> image format needed </param>
		/// <param name="wrap"> image wrapping option </param>
		/// <param name="texOrder"> order id Of Tex, used for material shader texture bind pass, if material uses only 1 texture set to 0 </param>
		static void CreateTexture2D(std::string name, std::string path, int reqComp, TextureFormat texFormat, TextureWrap wrap, int texOrder = 0);

		/// <summary>
		/// This Method Creates a Texture2D using the parameters provided and saved in runtime
		/// cache to re - use by using the name specified.
		/// </summary>
		/// <param name="path"> path to image for texture </param>
		/// <param name="reqComp"> required compression, if unsure set to 0</param>
		/// <param name="texFormat"> image format needed </param>
		/// <param name="wrap"> image wrapping option </param>
		/// <param name="texOrder"> order id Of Tex, used for material shader texture bind pass, if material uses only 1 texture set to 0 </param>
		/// <returns>auto generated ID</returns>
		static std::string CreateTexture2D(std::string path, int reqComp, TextureFormat texFormat, TextureWrap wrap, int texOrder = 0);


		/// <summary>
		/// This Method Creates a Shader using the parameters provided and saved in runtime
		/// cache to re - use by using the name specified
		/// </summary>
		/// <param name="name"> key used to store in cache </param>
		/// <param name="vertShaderPath"> vert shade path </param>
		/// <param name="fragShaderPath"> fram shader path </param>
		static void CreateShader(std::string name, std::string shaderPath);

		/// <summary>
		/// This Method Creates a Shader using the parameters provided and saved in runtime
		/// cache to re - use by using the name specified
		/// </summary>
		/// <param name="name"> key used to store in cache </param>
		/// <param name="vertShaderPath"> vert shade path </param>
		/// <param name="fragShaderPath"> fram shader path </param>
		/// <returns>auto generated ID</returns>
		static std::string CreateShader(std::string shaderPath);

		/// <summary>
		/// This Method Creates a Material using the parameters provided and saved in runtime
		/// cache to re - use by using the name specified
		/// </summary>
		/// <param name="name"> key used to store in cache </param>
		/// <param name="shader"> shader to use </param>
		/// <param name="textures"> texture array to use </param>
		/// <param name="lenOfTex"> total no of elements in texture array </param>
		/// <returns>auto generated ID</returns>
		static void CreateMaterial(std::string name, Shader* shader, Texture2D* textures, int lenOfTex = 0);


		/// <summary>
		/// This Method Creates a Material using the parameters provided and saved in runtime
		/// cache to re - use by using the name specified
		/// </summary>
		/// <param name="name"> key used to store in cache </param>
		/// <param name="shader"> shader to use </param>
		/// <param name="textures"> texture array to use </param>
		/// <param name="lenOfTex"> total no of elements in texture array </param>
		/// <returns>auto generated ID</returns>
		static std::string CreateMaterial(Shader* shader, Texture2D* textures, int lenOfTex = 0);


		//Fetch methods

		/// <summary>
		/// Returns a shader using the name specified, NULL if doesn't exist
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		static Shader* GetShader(std::string name);

		/// <summary>
		/// Returns a texture2d using the name specified, NULL if doesn't exist
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		static Texture2D* GetTexture2D(std::string name);

		/// <summary>
		/// Returns a material using the name specified, NULL if doesn't exist
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		static Material* GetMaterial(std::string name);

		//Cleanup methods

		/// <summary>
		/// Deletes Shader with name specified
		/// </summary>
		/// <param name="name"></param>
		static void CleanShader(std::string name);

		/// <summary>
		/// Deletes Texture2D with name specified
		/// </summary>
		/// <param name="name"></param>
		static void CleanTexture2D(std::string name);

		/// <summary>
		/// Deletes Material with name specified
		/// </summary>
		/// <param name="name"></param>
		static void CleanMaterial(std::string name);

		/// <summary>
		/// Clean all resources data, use only towards end of game loop.
		/// Calle
		/// </summary>
		static void CleanAll();
	};
}

