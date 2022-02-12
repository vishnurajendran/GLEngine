#pragma once
#include "Core.h"
#include<string>
#include<map>

namespace GLengine {
	class GLENGINE_API Preferences {
		static std::map<std::string, std::string> prefMap;
		static bool isInitialised;
		static void AddLineAsKVPair(std::map<std::string, std::string>* mp, std::string entry);
	public:
		static void Initialise();
		static bool HasKey(std::string key);
		static void Remove(std::string key);

		static std::string GetString(std::string key);
		static int GetInt(std::string key);
		static float GetFloat(std::string key);

		static void SetString(std::string key, std::string value);
		static void SetInt(std::string key, int value);
		static void SetFloat(std::string key, float value);
	};
}