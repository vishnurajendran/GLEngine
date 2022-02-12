#pragma once
#ifdef GLENGINE_PLATFORM_WINDOWS
#ifdef BUILD_DLL
#define GLENGINE_API __declspec(dllexport)
#else 
#define GLENGINE_API __declspec(dllimport)
#endif
#else
#error GLEngine currently only supports Windows
#endif