#pragma once
#include "GLEngine/Core/Core.h"
namespace GLengine {
	GLENGINE_API char* ReadTextFile(const char* fileName);
	GLENGINE_API bool AppendToTextFile(const char* fileName, const char* textToWrite);
	GLENGINE_API bool WriteTextFile(const char* fileName, const char* textToWrite);
	GLENGINE_API bool DirExists(const char* path);
	GLENGINE_API bool FileExists(const char* path);
	GLENGINE_API void MakeDirectory(const char* path);
}

